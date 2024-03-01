################################################################################
# Сборщик проекта
################################################################################

C_SRCS += \
./project/matrix/exceptions.cpp \
./project/matrix/matrix.cpp

C_DEPS += \
./project/matrix/exceptions.d \
./project/matrix/matrix.d

OBJS += \
./project/matrix/exceptions.o \
./project/matrix/matrix.o

project/matrix/%.o: ./project/matrix/%.cpp
	@echo 'Цель построения: $<'
	@echo 'Операция: Compiler'
	g++ -Wall -Wextra -Werror -ansi -std=c++17 -O3 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Цель готового здания: $<'
	@echo ' '


