#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define THRESHOLD 0.00001

typedef struct {
    char name[20];
    int id;
    float wage;
}Employee;

Employee employees[] = {
    {"Maks", 123, 420.69},
    {"Jan", 124, 213.7},
    {"John", 125, 312.34},
    {"Adam", 126, 890.45},
    {"Mike", 127, 123.5},
    {"Jan", 128, 876.5},
    {"Emma", 129, 7849.54},
    {"William", 130, 4823.6},
};

int inteagers[] = {1, 7, 3, 67, 234, 2, -6, -34, 54};
float f_numbers[] = {234.54, -123.4, 1.2314, 765.2, -21.37};

void* bsearch(const void *key, const void *ptr, size_t count, size_t size, int (*comp)(const void*, const void*));
Employee* find_name(const char* name);
int comp_name(const void* ptr1, const void* ptr2);
Employee* find_id(int id);
int comp_id(const void* ptr1, const void* ptr2);
Employee* find_wage(float wage);
int comp_wage(const void* ptr1, const void* ptr2);
int* find_int(int num);
int comp_int(const void* ptr1, const void* ptr2);
float* find_float(float num);
int comp_float(const void* ptr1, const void* ptr2);
void print_employee(Employee* employee);


void* bsearch(const void *key, const void *ptr, size_t count, size_t size, int (*comp)(const void*, const void*)) {
    int first = 0;
    int mid;
    int last = count;
    const void* curr_element = 0;
    int key_element;

    while (first <= last) {
        mid = ((last - first) / 2) + first;
        curr_element = (char*)ptr + mid * size;
        key_element = (*comp)(key, curr_element);

        if (key_element == 0)
            return ((void*)curr_element);
        else if (key_element < 0)
            last = mid - 1;
        else
            first = mid + 1;
    }

    return NULL;
}

Employee* find_name(const char* name) {
    Employee employee;
    strcpy(employee.name, name);
    if (bsearch(&employee, employees, sizeof(employees) / sizeof(*employees),  sizeof(*employees), comp_name) == NULL) {
        printf("\nNo matching name.\n");
        return NULL;
    }
    else 
        return bsearch(&employee, employees, sizeof(employees) / sizeof(*employees),  sizeof(*employees), comp_name);
}

int comp_name(const void* ptr1, const void* ptr2) {
    return strcmp(((Employee*)ptr1)->name, ((Employee*)ptr2)->name);
}

Employee* find_id(int id) {
    Employee employee;
    employee.id = id;
    if (bsearch(&employee, employees, sizeof(employees) / sizeof(*employees),  sizeof(*employees), comp_id) == NULL) {
        printf("\nNo matching id.\n");
        return NULL;
    }
    else 
        return bsearch(&employee, employees, sizeof(employees) / sizeof(*employees),  sizeof(*employees), comp_id);
}

int comp_id(const void* ptr1, const void* ptr2) {
    return (((Employee*)ptr1)->id - ((Employee*)ptr2)->id);
}

Employee* find_wage(float wage) {
    Employee employee;
    employee.wage = wage;
    if (bsearch(&employee, employees, sizeof(employees) / sizeof(*employees),  sizeof(*employees), comp_wage) == NULL) {
        printf("\nNo matching id.\n");
        return NULL;
    }
    else 
        return bsearch(&employee, employees, sizeof(employees) / sizeof(*employees),  sizeof(*employees), comp_wage);
}

int comp_wage(const void* ptr1, const void* ptr2) {
    if (fabs((((Employee*)ptr1)->wage - ((Employee*)ptr2)->wage)) < 0.00001)
        return 0;
    else {
        if ((((Employee*)ptr1)->wage - ((Employee*)ptr2)->wage) > 0)
            return 1;
        else 
            return -1;
    }
}

int* find_int(int num) {
    int temp;
    temp = num;
    if (bsearch(&temp, inteagers, sizeof(inteagers) / sizeof(*inteagers), sizeof(*inteagers), comp_int) == NULL) {
        printf("\nNo matching number.\n");
        return NULL;
    }
    else 
        return bsearch(&temp, inteagers, sizeof(inteagers) / sizeof(*inteagers), sizeof(*inteagers), comp_int);
}

int comp_int(const void* ptr1, const void* ptr2) {
    return (*(int*)ptr1 - *(int*)ptr2);
}

float* find_float(float num) {
    float temp;
    temp = num;
    if (bsearch(&temp, f_numbers, sizeof(f_numbers) / sizeof(*f_numbers), sizeof(*f_numbers), comp_float) == NULL) {
        printf("\nNo matching number.\n");
        return NULL;
    }
    else 
        return bsearch(&temp, f_numbers, sizeof(f_numbers) / sizeof(*f_numbers), sizeof(*f_numbers), comp_float);
}

int comp_float(const void* ptr1, const void* ptr2) {
    if (fabs(*(float*)ptr1 - *(float*)ptr2) < THRESHOLD)  
        return 0;
    else {
        if (*(float*)ptr1 - *(float*)ptr2 > 0)
            return 1;
        else 
            return -1;
    }
}

void print_employee(Employee* employee) {
    if (employee != NULL)
        printf("\nName: %s\nID:   %d\nWage: $%.2f\n\n", employee->name, employee->id, employee->wage);
}

void print_int(int* num) {
    if (num != NULL)
        printf("Found number: %d\n", *num);
}

void print_float(float* num) {
    if (num != NULL)
        printf("Found number: %.2f\n", *num);
}

int main() {
    char name[] = "Jan";
    int id = 127;
    float wage = 213.7;
    int inteager = 67;
    float f_num = -123.4;
    
    qsort(employees, sizeof(employees) / sizeof(*employees), sizeof(*employees), comp_name);
    printf("---------------------\n");
    printf("Looking for: %s\n", name);
    print_employee(find_name(name));

    qsort(employees, sizeof(employees) / sizeof(*employees), sizeof(*employees), comp_id);
    printf("---------------------\n");
    printf("Looking for: %d\n", id);
    print_employee(find_id(id));

    qsort(employees, sizeof(employees) / sizeof(*employees), sizeof(*employees), comp_wage);
    printf("---------------------\n");
    printf("Looking for: %.2f\n", wage);
    print_employee(find_wage(wage));
    printf("---------------------\n");

    qsort(inteagers, sizeof(inteagers) / sizeof(*inteagers), sizeof(*inteagers), comp_int);
    printf("Looking for: %d\n", inteager);
    print_int(find_int(inteager));
    printf("\n---------------------\n");

    qsort(f_numbers, sizeof(f_numbers) / sizeof(*f_numbers), sizeof(*f_numbers), comp_float);
    printf("Looking for: %.2f\n", f_num);
    print_float(find_float(f_num));
    printf("\n---------------------\n");

    return 0;
}
