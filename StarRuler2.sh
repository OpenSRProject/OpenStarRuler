#!/bin/bash
set -eo pipefail

#Figure out where the script is located
if [[ -L "$0" ]]; then
	script_loc="$(readlink "$0")"
else
	script_loc="$0"
fi
cd "$(dirname "$script_loc")"

bin_folder="bin"
args=()
for arg in "$@"; do
    if [ "$arg" = "--legacy" ]; then
        bin_folder="bin_legacy"
    else
        args+=("$arg")
    fi
done

#Execute the right binary for this architecture
if [ "$(uname)" = "Darwin" ]; then
    chmod +x ./$bin_folder/osx64/StarRuler2.bin
    DYLD_LIBRARY_PATH="./$bin_folder/osx64/:$DYLD_LIBRARY_PATH" exec ./$bin_folder/osx64/StarRuler2.bin "${args[@]}"
elif [ "$(uname -m)" = "x86_64" ]; then
    chmod +x ./$bin_folder/lin64/StarRuler2.bin
    LD_LIBRARY_PATH="./$bin_folder/lin64/:$LD_LIBRARY_PATH" exec ./$bin_folder/lin64/StarRuler2.bin "${args[@]}"
else
    chmod +x ./$bin_folder/lin32/StarRuler2.bin
    LD_LIBRARY_PATH="./$bin_folder/lin32/:$LD_LIBRARY_PATH" exec ./$bin_folder/lin32/StarRuler2.bin "${args[@]}"
fi;
# vim: set ff=unix:
