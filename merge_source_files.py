#!/usr/bin/env python
import sys
import os
import re

class Merger(object):

    include_pattern = r"^\#\s*include\s*\"([a-zA-Z0-9_\.]*)\"|^\#\s*pragma\s+once"

    def __init__(self, include_paths):
        self._merged_files = set()
        self._include_paths = include_paths

    def _merge_helper(self, input_file_path):
        if input_file_path in self._merged_files:
            return ""

        self._merged_files.add(input_file_path)
        input_file_content = ""
        with open(input_file_path, "r") as ifile:
            input_file_content = ifile.read()

        output_file_content = ""
        input_read_iterator = 0
        for match in re.finditer(Merger.include_pattern, input_file_content, re.M):
            output_file_content += input_file_content[input_read_iterator:match.start(0)]
            input_read_iterator = match.end(0)+1

            if match[0][-1] == '"':
                file_name = match.group(1)
                for include_path in self._include_paths:
                    full_file_path = os.path.join(include_path, file_name)
                    if os.path.exists(full_file_path):
                        output_file_content += self._merge_helper(full_file_path)
                        break

        output_file_content += input_file_content[input_read_iterator:]
        return output_file_content

    def merge(self, input_file_path, output_file_path):
        with open(output_file_path, "w") as ofile:
            ofile.write(self._merge_helper(input_file_path))

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: merge_source_files input_file_path project_root_directory output_file_path")
        print("invoked with: {}".format(" ".join(sys.argv[1:])))
        sys.exit(1)

    input_file_path = os.path.abspath(sys.argv[1])
    output_file_path = os.path.abspath(sys.argv[3])
    project_include_directory = os.path.join(os.path.abspath(os.path.dirname(__file__)), "src")
    tools_include_directory = os.path.abspath(sys.argv[2])

    merger = Merger([tools_include_directory, project_include_directory])
    merger.merge(input_file_path, output_file_path)
