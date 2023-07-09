import sys
import os
from typing import List


def compile_shaders(shaders: List[str]) -> None:
    """
    Compiles shaders from a given list of filenames.
    """

    for shader in shaders:
        os.system(f'env/glslc shaders/{shader} -o shaders/{shader}.spv')


if __name__ == '__main__':
    shaders = sys.argv[1:]

    compile_shaders(shaders)