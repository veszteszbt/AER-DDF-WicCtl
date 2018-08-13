#define LIBSSH_STATIC 1
#include <libssh/libssh.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <errno.h>

int authenticate_pubkey(ssh_session session)
{
  int rc;
  rc = ssh_userauth_publickey_auto(session, NULL, NULL);
  if (rc == SSH_AUTH_ERROR)
  {
	 fprintf(stderr, "Authentication failed: %s\n",
	   ssh_get_error(session));
	 return SSH_AUTH_ERROR;
  }
  return rc;
}

int main()
{
  ssh_session session;
  ssh_channel channel;
  int rc;
  int pubkey;
  int port = 6022;
  char *password;

  session = ssh_new();
  if (session == NULL)
	exit(-1);

  ssh_options_set(session, SSH_OPTIONS_HOST, "127.0.0.1");
  ssh_options_set(session, SSH_OPTIONS_PORT, &port);
  rc = ssh_connect(session);
  if (rc != SSH_OK)
  {
	fprintf(stderr, "Error connecting to localhost: %s\n",
			ssh_get_error(session));
	exit(-1);
  }

  password = getpass("Password: ");
  rc = ssh_userauth_password(session, NULL, password);
  if (rc != SSH_AUTH_SUCCESS)
  {
	fprintf(stderr, "Error authenticating with password: %s\n",
			ssh_get_error(session));
	ssh_disconnect(session);
	ssh_free(session);
	exit(-1);
  }

  channel = ssh_channel_new(session);
	rc = ssh_channel_open_session(channel);
	std::cout << "data written\n";
	if(rc !=SSH_OK)
	{
		fprintf(stderr, "Error : %s\n",
				ssh_get_error(session));
		ssh_disconnect(session);
		ssh_free(session);
		exit(-1); 
	}

  int nbytes;
  int nwritten;
  	char buffer[10000];
  int cnt = 0;
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
		if(cnt++)
			break;
  }

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

	}

  ssh_channel_send_eof(channel);
	ssh_channel_free(channel);
  ssh_disconnect(session);
  ssh_free(session);
}