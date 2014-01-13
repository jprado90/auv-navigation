/*
 * Simulador de una MTi-G de Xsens
 *
 * Derechos Reservados © 2013 GARP y colaboradores
 *
 * Este es un Software Libre; como tal redistribuirlo y/o modificarlo está
 * permitido, siempre y cuando se haga bajo los términos y condiciones de la
 * Licencia Pública General GNU publicada por la Free Software Foundation, ya
 * sea en su versión 2 ó cualquier otra de las posteriores a la misma.
 *
 * Este “Programa” se distribuye con la intención de que sea útil, sin embargo
 * carece de garantía, ni siquiera tiene la garantía implícita de tipo comercial
 * o inherente al propósito del mismo “Programa”. Ver la Licencia Pública
 * General GNU para más detalles.
 *
 * Se debe haber recibido una copia de la Licencia Pública General GNU con este
 * “Programa”, si este no fue el caso, favor de escribir a la Free Software
 * Foundation, Inc., 59 Temple Place – Suite 330, Boston, MA 02111-1307, USA.
 */

#define _POSIX_C_SOURCE 199506L

#include <time.h>
#include <string.h>
#include <math.h>

#include <fcntl.h>
#include <sys/time.h>

#include "garp/mt.h"

int main(int argc, char *argv[]) {
	int fd, angle = 0, increase = 1;
	struct mt_message message;
	float content[65];
	struct timespec init, end;

	message.content = (unsigned char *)content;

	memset(content, 0, 260);
	message.type = 0x32;
	message.length = 73;

	fd = open(argv[1], O_WRONLY);

	while(1){
		clock_gettime(CLOCK_REALTIME, &init);

		content[0] = sin(3.1416 * angle / 180);
		if(angle == 360) angle = 0;
		else angle = angle + increase;

		mt_send(fd, 0xff, &message);
		clock_gettime(CLOCK_REALTIME, &end);

		/* teniendo fe en que esto demorará menos de un segundo */
		end.tv_sec = 0;
		end.tv_nsec -= init.tv_nsec;
		end.tv_nsec = 10000000 - end.tv_nsec;

		nanosleep(&end, NULL);
	}

	return 0;
}