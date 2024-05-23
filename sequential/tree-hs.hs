import System.CPUTime
import Text.Printf

data Node = Node {
    val :: Integer,
    left :: Maybe Node,
    right :: Maybe Node
} deriving (Show)

gen :: Integer -> Integer -> Integer -> Maybe Node
gen depth height val
    | height < depth = Just Node {
        val = val,
        left = gen depth (height + 1) (2 * val),
        right = gen depth (height + 1) (2 * val + 1)
    }
    | otherwise = Nothing

sumTree :: Maybe Node -> Integer
sumTree Nothing = 0
sumTree (Just (Node val left right)) = val + sumTree left + sumTree right

main :: IO ()
main = do
    start <- getCPUTime
    let tree = gen 20 0 1
    printf "Result(Haskell): %d\n" (sumTree tree)
    end <- getCPUTime
    let diff = (fromIntegral (end - start)) / (10^12)
    printf "- TIME(Haskell): %.2fs\n" (diff :: Double)