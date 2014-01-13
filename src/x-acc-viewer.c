/*
 * Visualizador de la aceleración en el eje X registrada por la IMU que emplea
 * como proveedor de datos el servidor del HMI Sharksoft.
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

#include <assert.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/select.h>

#include "garp/garpnet.h"

int main(int argc, char *argv[]) {
	int fd, retval;
	fd_set fds;
	struct garpnet_message message;
	float content[65];
	struct timeval timeout;

	message.content = (unsigned char *)content;

	memset(content, 0, 260);

	fd = open(argv[1], O_RDWR);
	assert(fd != -1);

	FD_ZERO(&fds);
	FD_SET(fd, &fds);

	printf("entrando en el ciclo\n");

	while(1){
		message.type = 0x02;
		message.length = 0;

		if(garpnet_tx(fd, 1, &message) == -1){
			printf("send error\n");
		}else{
			fd_set fds2 = fds;
			timeout.tv_sec = 1;
			timeout.tv_usec = 0;

			printf("message tx\n");
			retval = select(fd + 1, &fds2, NULL, NULL, &timeout);

			if(retval == 0){
				printf("read timeout\n");
			}else{
				printf("i/o ready\n");
				if(garpnet_rx(fd, 0, &message) != -1 && message.type == 0x0E){
					printf("%f\n", content[0]);}
				else
					printf("receive error\n");
			}
		}

		sleep(1);
	}

	return 0;
}