if [ $# -ne 3 ]; then
	echo "Usage: malloc_debug <first_malloc> <last_malloc> <in_file>"
	exit 1
fi

rm log logerr
make leaks
for ((i = $1; i <= $2; i++)); do
	echo $i
	make malloc_debug when=$i
	./minishell < $3 >> log 2>> logerr
done