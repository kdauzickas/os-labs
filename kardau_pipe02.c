#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char * argv[]){
   int      fd[2], status;
   pid_t    pid, x;
   long input_file_size;
   FILE *input_file;
   char *file_contents;

   if (argc != 2) {
      puts("Reikia failo pavadinimo");
      exit(1);
   }

   if( pipe( fd ) == -1 ){
      fprintf( stderr, "Nepavyko sukurti programinio kanalo !\n" );
      exit( 1 );
   }

   input_file = fopen(argv[1], "rb");
   fseek(input_file, 0, SEEK_END);
   input_file_size = ftell(input_file);

   pid = fork();
   if( pid != 0 && pid != -1 ){
      rewind(input_file);
      file_contents = malloc(input_file_size * (sizeof(char)));
      fread(file_contents, sizeof(char), input_file_size, input_file);
      fclose(input_file);

      if( write( fd[1], file_contents, sizeof( file_contents ) ) != sizeof( file_contents ) ){
         fprintf( stderr, "Klaida rasant" );
         exit( 2 );
      }

      x = wait( &status );
      return 0;
   }
   else if (pid == 0) {
      file_contents = malloc(input_file_size * (sizeof(char)));
      read( fd[0], file_contents, sizeof( file_contents ) );

      puts(file_contents);
      return 0;
   }
   else if( pid == -1 ){ 
      fprintf ( stderr, "Nepavyko sukurti vaiko !\n" );
      exit( 4 );
   }

}
