#!/bin/sh

output_file_name=${1%.*}
make_command="gcc -g -o $output_file_name $1"

echo "use -k after filename to keep output binary file"
echo "[INFO] $make_command " 
eval $make_command
if [[ $? == 0 ]]; then 
    echo -e "[INFO] compilation completed with err code '$?'\n"
    echo "[EXEC] ./$output_file_name "
    echo -e "[OUT]\n $(eval "./$output_file_name")"
else
    echo "[ERR] compilatioin failed with err code '$?'"
fi
if [[ $2 != "-k" ]]; then
    echo -e "\n[INFO] cleaning files: rm -rf $output_file_name"
    rm -rf $output_file_name
fi

