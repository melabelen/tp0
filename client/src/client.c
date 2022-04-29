#include "client.h"
#include <commons/log.h>
#include <commons/config.h>
#include<readline/readline.h>




int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = log_create("tp0.log","Process name",true,LOG_LEVEL_INFO);

	log_info(logger,"Hola! Soy un log");

	config = config_create("cliente.config");

		ip = config_get_string_value(config, "IP");
		puerto = config_get_string_value(config, "PUERTO");
		valor = config_get_string_value(config, "CLAVE");

	/* ---------------- ARCHIVOS DE CONFIGURACION ----------------



	log_info(logger,ip);
	log_info(logger,puerto);
	log_info(logger,valor);

*/


	/* ---------------- LEER DE CONSOLA ----------------

	//leer_consola(logger);

	log_destroy(logger);
	config_destroy(config);
*/

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(valor, conexion);

	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	leido = readline("> ");
	log_info(logger,leido);

	while(leido[0] != '\0'){
		log_info(logger,leido);
		leido = readline("> ");

	}
	free(leido);

	return;

}

void paquete(int conexion)
{
	char* leido;
	t_paquete* paquete;
	paquete = crear_paquete();

	leido = readline("> ");
	while(strcmp(leido, "")){
		 	agregar_a_paquete(paquete, leido, sizeof(leido));
			leido = readline("> ");
		}


	enviar_paquete(paquete, conexion);

	free(leido);
	eliminar_paquete(paquete);

	return;

}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	liberar_conexion(conexion);
	log_destroy(logger);
	config_destroy(config);
}
