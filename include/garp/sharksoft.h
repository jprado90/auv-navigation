/*
 * Servidor de Datos para el HMI Sharksoft.
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

#ifndef _GARP_SHARKSOFT_H_
#define _GARP_SHARKSOFT_H_

#include <libconfig.h>

#include "garp/garpnet.h"

#include "garp/vector3d.h"
#include "garp/imu.h"

#define SHARKSOFT_ACK 0x00
#define SHARKSOFT_GETDATA 0x02
#define SHARKSOFT_SETDATA 0x0E

struct sharksoft {
	/*! Descriptor de fichero asociado al HMI Sharksoft. */
	int fd;

	/*! Puntero al medio de almacenamiento de la información de la IMU */
	struct imu * imu_ptr;

	struct vector3d * gps_ptr;

	struct garpnet_message message;

	unsigned char content[260];
};

void sharksoft_init(struct sharksoft * sharksoft, config_setting_t * config,
					struct imu * imu_ptr, struct vector3d * gps_ptr);
void sharksoft_handle_request(struct sharksoft * sharksoft);

#endif /* _GARP_SHARKSOFT_H_ */
