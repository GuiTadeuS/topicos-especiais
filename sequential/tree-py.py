from dataclasses import dataclass
import time

@dataclass
class Node:
    val: int
    left: 'Node' = None
    right: 'Node' = None

class Leaf:
    pass

def sum_tree(tree):
    if isinstance(tree, Leaf):
        return 0
    else:
        return tree.val + sum_tree(tree.left) + sum_tree(tree.right)

def gen(depth, height=0, val=1):
    if height < depth:
        return Node(val, gen(depth, height+1, 2*val), gen(depth, height+1, 2*val+1))
    else:
        return Leaf()

def main():
    return sum_tree(gen(20))

if __name__ == "__main__":
    start = time.time()
    print(f"Result(Python): {main()}")
    end = time.time()
    resultTime = end - start 
    print(f"- TIME(Python): {resultTime:.2f}s")
