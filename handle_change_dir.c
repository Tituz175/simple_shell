#include "main.h"

/**
 * cd_parent -> this function changes working
 * directory to the parent directory
 * @s_datas: shell data structure needed for this function
 */
void cd_parent(st_shell *s_datas)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);
	set_myenv("OLDPWD", cp_pwd, s_datas);
	dir = s_datas->args[1];
	if (_strcmp(".", dir) == 0)
	{
		set_myenv("PWD", cp_pwd, s_datas);
		free(cp_pwd);
		return;
	}
	if (_strcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	rev_string(cp_strtok_pwd);
	cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _strtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			rev_string(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		set_myenv("PWD", cp_strtok_pwd, s_datas);
	}
	else
	{
		chdir("/");
		set_myenv("PWD", "/", s_datas);
	}
	s_datas->status = 0;
	free(cp_pwd);
}

/**
 * cd_to -> this function changes working directory
 * to the given directory by the user.
 * @s_datas: shell data structure needed for this function
 */
void cd_to(st_shell *s_datas)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = s_datas->args[1];
	if (chdir(dir) == -1)
	{
		error_info(s_datas, 2);
		return;
	}

	cp_pwd = _strdup(pwd);
	set_myenv("OLDPWD", cp_pwd, s_datas);

	cp_dir = _strdup(dir);
	set_myenv("PWD", cp_dir, s_datas);

	free(cp_pwd);
	free(cp_dir);

	s_datas->status = 0;

	chdir(dir);
}

/**
 * cd_previous -> this function changes working directory
 * to the last directory access by the user.
 * @s_datas: shell data structure needed for this function
 */
void cd_previous(st_shell *s_datas)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);

	p_oldpwd = _mygetenv("OLDPWD", s_datas->_environ);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _strdup(p_oldpwd);

	set_myenv("OLDPWD", cp_pwd, s_datas);

	if (chdir(cp_oldpwd) == -1)
		set_myenv("PWD", cp_pwd, s_datas);
	else
		set_myenv("PWD", cp_oldpwd, s_datas);

	p_pwd = _mygetenv("PWD", s_datas->_environ);

	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	s_datas->status = 0;

	chdir(p_pwd);
}

/**
 * cd_home -> this function changes the working directory
 * to the home directory.
 * @s_datas: shell data structure needed for this function
 */
void cd_home(st_shell *s_datas)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);

	home = _mygetenv("HOME", s_datas->_environ);

	if (home == NULL)
	{
		set_myenv("OLDPWD", p_pwd, s_datas);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		error_info(s_datas, 2);
		free(p_pwd);
		return;
	}

	set_myenv("OLDPWD", p_pwd, s_datas);
	set_myenv("PWD", home, s_datas);
	free(p_pwd);
	s_datas->status = 0;
}

/**
 * manage_cd -> this function manage the change directory
 * function.
 * @s_datas: shell data structure needed for this function
 * Return: 1 on success
 */
int manage_cd(st_shell *s_datas)
{
	char *dir = s_datas->args[1];

	if (dir == NULL || _strcmp(dir, "$HOME") == 0 ||
		_strcmp(dir, "~") == 0 || _strcmp(dir, "--") == 0)
	{
		cd_home(s_datas);
		return (1);
	}

	if (_strcmp(dir, "-") == 0)
	{
		cd_previous(s_datas);
		return (1);
	}

	if (_strcmp(dir, ".") == 0 || _strcmp(dir, "..") == 0)
	{
		cd_parent(s_datas);
		return (1);
	}

	cd_to(s_datas);

	return (1);
}
