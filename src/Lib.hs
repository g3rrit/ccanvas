{-# LANGUAGE ForeignFunctionInterface #-}
{-# LANGUAGE GeneralizedNewtypeDeriving #-}

module Lib where

import Foreign
import Foreign.C.Types

import Control.Monad.State

foreign import ccall "init" c_init :: CUInt -> CUInt -> IO (Ptr ())
foreign import ccall "quit" c_quit :: Ptr () -> IO ()
foreign import ccall "put_pixel" c_putPixel :: Ptr () -> CUInt -> CUInt -> CUChar -> CUChar -> CUChar -> CUChar -> IO ()
foreign import ccall "clear_screen" c_clearScreen :: Ptr () -> IO ()
foreign import ccall "event_loop" c_eventLoop :: Ptr () -> IO ()

newtype CS a = CS { runCS :: StateT (Ptr ()) IO a }
  deriving (Functor, Applicative, Monad, MonadState (Ptr ()), MonadIO)

intCUInt :: Word -> CUInt
intCUInt = fromInteger . toInteger

charCUChar :: Word8 -> CUChar
charCUChar = fromInteger . toInteger

execCS :: Word -> Word -> CS a -> IO a
execCS x y cs = do
  cc <- c_init (intCUInt x) (intCUInt y)
  (a, cc') <- runStateT (runCS cs) cc
  c_quit cc'
  return a

data Color = Color Word8 Word8 Word8 Word8

putPixel :: Word -> Word -> Color -> CS ()
putPixel x y (Color r g b a) = do
  cc <- get
  liftIO $ c_putPixel cc (fromInteger $ toInteger x) (fromInteger $ toInteger y)
    (charCUChar r)
    (charCUChar g)
    (charCUChar b)
    (charCUChar a)

clearScreen :: CS ()
clearScreen = do
  cc <- get
  liftIO $ c_clearScreen cc

loop :: CS ()
loop = do
  cc <- get
  liftIO $ c_eventLoop cc

draw :: IO ()
draw = do
  execCS 400 600 $ do
    putPixel 10 10 $ Color 255 0 0 0
    loop
