import sys
import os
import subprocess
from typing import List
from utils.terminal import Terminal


def compile_shaders(shaders: List[str]) -> None:
    """
    Compiles shaders from a given list of filenames.
    """

    for shader in shaders:
        proc = subprocess.run([f'env/glslc shaders/{shader} -o shaders/{shader}.spv'], stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True, text=True)
        out = proc.stderr.strip('\n')

        if out:
            Terminal.print(f'[-] {out}', [Terminal.FAIL])
        else:
            Terminal.print(f'[+] {shader} compiled', [Terminal.OKGREEN])

if __name__ == '__main__':
    shaders = sys.argv[1:]

    compile_shaders(shaders)