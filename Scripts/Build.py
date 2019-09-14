#
# Copyright 2018 Vladimir Balun
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

BUILD_DIR = '../Build'


def is_build_with_clean():
    import argparse
    parser = argparse.ArgumentParser(description='Script to build the solution.')
    parser.add_argument('-c', '--clean', action='store_true', help='clean old solution version')
    args = parser.parse_args()
    return args.clean


def remove_old_solution():
    try:
        import shutil
        shutil.rmtree(BUILD_DIR)
        return True
    except OSError:
        return False


def is_program_installed(program_name):
    from shutil import which
    return which(program_name)


def run_command(cmd):
    import subprocess
    process = subprocess.Popen(cmd, stdout=subprocess.PIPE)
    process.wait()
    for line in process.stdout:
        print(line)


if __name__ == '__main__':
    if is_build_with_clean():
        if remove_old_solution():
            print('Old solution cleaned successfully.')
        else:
            import sys
            sys.stderr.write('Old solution folder was not cleaned.\n')
            sys.stderr.write('New solution will not be generated.')
            exit()

    if not is_program_installed('cmake'):
        import sys
        sys.stderr.write('CMake is not installed on your PC.\n')
        exit()

    command = BUILD_DIR + 'cmake ..'
    run_command(command)
