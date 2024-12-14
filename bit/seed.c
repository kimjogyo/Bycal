#include <stdio.h>
#include <stdlib.h>

int main() {
    // Step 1: Write the C code to aaa.c
    FILE *file = fopen("aaa.c", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    const char *code = "#include <stdio.h>\n"
                       "int main() {\n"
                       "    int a;\n"
                       "    a = 1 + 5000;\n"
                       "    printf(\"%d\\n\", a);\n"
                       "    return 0;\n"
                       "}\n";

    fprintf(file, "%s", code);
    fclose(file);

    // Step 2: Compile the generated C file
    int compile_result = system("gcc aaa.c -o aaa");
    if (compile_result != 0) {
        perror("Error compiling the code");
        return 1;
    }
    
/*    
    int run_result = system("./aaa");
    if (run_result != 0) {
        perror("Error running the compiled program");
        return 1;
    }
*/


    // Step 3: Run the compiled program and capture its output
    FILE *fp = popen("./aaa", "r");
    if (fp == NULL) {
        perror("Error running compiled program");
        return 1;
    }

    char result[100];
    if (fgets(result, sizeof(result), fp) != NULL) {
        printf("Output of aaa: %s", result);
    } else {
        printf("No output from the program\n");
    }

    pclose(fp);
    
   
    
    
    
    
    return 0;
}
