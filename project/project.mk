################################################################################
# Сборщик проекта
################################################################################

C_SRCS += \
./project/main.cpp

C_DEPS += \
./project/main.d

OBJS += \
./project/main.o 

project/%.o: ./project/%.cpp
	@echo 'Цель построения: $<'
	@echo 'Операция: Compiler'
	g++ -Wall -Wextra -Werror -ansi -std=c++17 -O3 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Цель готового здания: $<'
	@echo ' '


