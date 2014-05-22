#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>
#include <stdlib.h>

static int pagrindinis;
static int vaikas;

void il_catch_USR1( int );       /* signalo apdorojimo f-ja */
void il_catch_USR2( int );       /* signalo apdorojimo f-ja */
int il_child( void );            /* vaiko proceso veiksmai */
int il_parent( void );      /* tevo proceso veiksmai */

int il_child( void ){
   signal(SIGUSR1, il_catch_USR1);
   sleep( 10 );
}

int il_parent(){
   signal(SIGUSR2, il_catch_USR2);
   sleep(2);
   puts("Tevas siuncia SIGUSR1");
   kill(vaikas, SIGUSR1);
   return 0;
}

void il_catch_USR1( int snum ) {
    puts("Gautas SIGUSR1");
    system("who");
    kill(pagrindinis, SIGUSR2);
    sleep(5);
}

void il_catch_USR2( int snum ) {
    puts("Gautas SIGUSR2");

    kill(vaikas, SIGTERM);
    sleep(5);
    puts("Baigiam");
    exit(0);
}


int main( int argc, char **arg ){
   pid_t pid;
   pagrindinis = getpid();

   switch( pid = fork() ){
      case 0:
         il_child();
         break;
      default:
         vaikas = pid;
         il_parent();
         break;
      case -1:
         perror("fork");
         exit(1);
   }
   sleep(10);
   exit(0);
}
