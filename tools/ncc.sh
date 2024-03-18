my_array=(A B C D E F G H I J K L M N O P Q R S T U V W X Y Z)
for (( i = 0; i < $1; i++ )); do
	cp D:/cp/tools/default.cpp ${my_array[i]}.cpp
	subl ${my_array[i]}.cpp
done