################################################################################
# Сборщик проекта
################################################################################

C_SRCS += \
./project/matrix/test/test_base_operation.cpp \
./project/matrix/test/test_math_base_operation.cpp \
./project/matrix/test/test_math_pro_operation.cpp \
./project/matrix/test/test.cpp \
./project/matrix/test/utils.cpp

C_DEPS += \
./project/matrix/test/test_base_operation.d \
./project/matrix/test/test_math_base_operation.d \
./project/matrix/test/test_math_pro_operation.d \
./project/matrix/test/test.d \
./project/matrix/test/utils.d

OBJS += \
./project/matrix/test/test_base_operation.o \
./project/matrix/test/test_math_base_operation.o \
./project/matrix/test/test_math_pro_operation.o \
./project/matrix/test/test.o \
./project/matrix/test/utils.o

project/matrix/test/%.o: ./project/matrix/test/%.cpp
	@echo 'Цель построения: $<'
	@echo 'Операция: Compiler'
	g++ -Wall -Wextra -Werror -ansi -std=c++17 -O3 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Цель готового здания: $<'
	@echo ' '


