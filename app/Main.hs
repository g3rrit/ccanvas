module Main where

import Lib

main :: IO ()
main = execCS 400 600 $ do
  clearScreen $ Color 0 0 255 0
  putPixel 10 10 $ Color 255 0 0 0
  loop
