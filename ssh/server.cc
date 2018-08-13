#include <libssh/libssh.h> 
#include <libssh/server.h> 
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>

#ifndef KEYS_FOLDER
#ifdef _WIN32
#define KEYS_FOLDER
#else
#define KEYS_FOLDER "/etc/ssh/"
#endif
#endif

#define SSHD_USER "root"
#define SSHD_PASSWORD "x"

static int auth_password(const char *user, const char *password){
	if(strcmp(user, SSHD_USER))
		return 0;
	if(strcmp(password, SSHD_PASSWORD))
		return 0;
	return 1; // authenticated
}

static int authenticate(ssh_session session) {
	ssh_message message;
	do {
		message=ssh_message_get(session);

		if(!message)
			break;

		switch(ssh_message_type(message)){
			case SSH_REQUEST_AUTH:
				switch(ssh_message_subtype(message)){
					case SSH_AUTH_METHOD_PASSWORD:
						printf("User %s wants to auth with pass %s\n",
							   ssh_message_auth_user(message),
							   ssh_message_auth_password(message));
						if(
							auth_password(
								ssh_message_auth_user(message),
								ssh_message_auth_password(message)
							)
						)
						   {
							   printf("auth success\n");
							   ssh_message_auth_reply_success(message,0);
							   ssh_message_free(message);
							   return 1;
						   }
						printf("auth failed\n");
						ssh_message_auth_set_methods(message,
												SSH_AUTH_METHOD_PASSWORD |
												SSH_AUTH_METHOD_INTERACTIVE);
						// not authenticated, send default message
						ssh_message_reply_default(message);
						break;

					case SSH_AUTH_METHOD_NONE:
					default:
						printf("User %s wants to auth with unknown auth %d\n",
							   ssh_message_auth_user(message),
							   ssh_message_subtype(message));
						ssh_message_auth_set_methods(message,
												SSH_AUTH_METHOD_PASSWORD |
												SSH_AUTH_METHOD_INTERACTIVE);
						ssh_message_reply_default(message);
						break;
				}
				break;
			default:
				ssh_message_auth_set_methods(message,
												SSH_AUTH_METHOD_PASSWORD |
												SSH_AUTH_METHOD_INTERACTIVE);
				ssh_message_reply_default(message);
		}
		ssh_message_free(message);
	} while (1);
	return 0;
}

int main()
{
	ssh_session session;
	ssh_bind sshbind;
	ssh_message message;
	ssh_channel channel;
	char buffer[10000];
	int nbytes;
	int auth=0;
	int shell=0;
	int r;
	int verbosity = SSH_LOG_PROTOCOL;
	int port = 6022;
	session = ssh_new();
	sshbind = ssh_bind_new();
	if (session == NULL)
		exit(-1);
	
	if (sshbind == NULL)
		exit(-1);
	std::cout << "Precondition met\n";

	ssh_bind_options_set(sshbind,SSH_BIND_OPTIONS_BINDADDR,"127.0.0.1");
	ssh_bind_options_set(sshbind,SSH_BIND_OPTIONS_BINDPORT, &port);
	ssh_bind_options_set(sshbind, SSH_BIND_OPTIONS_DSAKEY,
											KEYS_FOLDER "ssh_host_dsa_key");
	ssh_bind_options_set(sshbind, SSH_BIND_OPTIONS_RSAKEY,
											KEYS_FOLDER "ssh_host_rsa_key");

	if(ssh_bind_listen(sshbind)<0){
		printf("Error listening to socket: %s\n", ssh_get_error(sshbind));
		return 1;
	}

	r = ssh_bind_accept(sshbind, session);
	if(r==SSH_ERROR){
	  printf("Error accepting a connection: %s\n", ssh_get_error(sshbind));
	  return 1;
	}

	if (ssh_handle_key_exchange(session)) {
		printf("ssh_handle_key_exchange: %s\n", ssh_get_error(session));
		return 1;
	}


	auth = authenticate(session);
	std::cout << "bind_accepted \n";
	if(!auth){
		printf("Authentication error: %s\n", ssh_get_error(session));
		ssh_disconnect(session);
		return 1;
	}
    do {
        message = ssh_message_get(session);
        if(message){
            if(ssh_message_type(message) == SSH_REQUEST_CHANNEL_OPEN &&
                    ssh_message_subtype(message) == SSH_CHANNEL_SESSION) {
                channel = ssh_message_channel_request_open_reply_accept(message);
				std::cout << "success \n";				
                ssh_message_free(message);
                break;
            } else {
				std::cout << "fail \n";				
                ssh_message_reply_default(message);
                ssh_message_free(message);
            }
        } else {
				std::cout << "failfail \n";				
            break;
        }
    } while(!channel);

    if(!channel) {
        printf("Error: client did not ask for a channel session (%s)\n",
                                                    ssh_get_error(session));
        ssh_finalize();
        return 1;
    }

	int cnt = 0;
	while(1)
	{
		nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0);
		if (nbytes < 0)
		{
			fprintf(stderr, "Error reading incoming data: %s\n",
					ssh_get_error(session));
			ssh_channel_send_eof(channel);
			ssh_channel_free(channel);
			return SSH_ERROR;
		}
		for(int i = 0; i < nbytes; ++i)
			std::cout << buffer[i];
		std::cout << std::endl;

		if(cnt++)
			break;
	}

	int nwritten;
	while(1)
	{
		std::string s;
		std::cin >> s;
		nbytes = s.length();
		nwritten = ssh_channel_write(channel, s.c_str(), nbytes);
		if(nbytes != nbytes)
		{
			fprintf(stderr, "Error reading incoming data: %s\n",
					ssh_get_error(session));
		}
		std::cout << "data written\n";
	}
	ssh_disconnect(session);
	ssh_bind_free(sshbind);

}