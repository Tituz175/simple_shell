/**
 * main -> Shell program entry point
 * @ac: argument count
 * @argv: argument vector
 * Return: 0 on success.
 *
 * This function serves as the entry point for the shell program.
 * It initializes shell data, sets up signal handling for interrupts,
 * and enters the main shell loop to process user commands.
 * After exiting the loop, it frees allocated resources and returns
 * the exit status of the shell.
 */
int main(int ac, char *argv[])
{
	st_shell s_datas; // Declare shell data structure
	(void) ac; // Ignore argument count for now

	// Set signal handler for interrupt (Ctrl+C)
	signal(SIGINT, get_sigint);
	// Initialize shell data with command line arguments
	set_data(&s_datas, argv);
	// Enter the main shell loop
	shell_loop(&s_datas);
	// Free allocated memory for shell data
	free_data(&s_datas);
	// Return the exit status of the shell
	if (s_datas.status < 0)
		return (255); // Return 255 for error status
	return (s_datas.status); // Return shell's exit status
}

/**
 * shell_prompt -> This function prints the shell prompt
 *
 * This function outputs the shell prompt symbol "($) " to 
 * indicate that the shell is ready to accept user input.
 */
void shell_prompt(void)
{
	write(STDIN_FILENO, "($) ", 4); // Write prompt to standard input
}

/**
 * shell_loop -> This function continuously reads user
 * input from stdin, processes it, and executes valid commands.
 * @s_datas: A pointer to a struct containing relevant shell data.
 *
 * This function represents the main loop of the shell.
 * It repeatedly displays the shell prompt, reads user input,
 * and processes that input. The input is filtered for comments, 
 * checked for syntax errors, and any variables are swapped before 
 * tokenization and execution of commands. The loop continues until 
 * EOF is encountered.
 */
void shell_loop(st_shell *s_datas)
{
	int loop_status, eof; // Loop status and end-of-file indicator
	char *input; // Pointer to hold user input

	loop_status = 1; // Initialize loop status to continue
	while (loop_status == 1)
	{
		shell_prompt(); // Display the shell prompt
		input = read_line(&eof); // Read user input, updating EOF status

		if (eof != -1) // Process input if it is not EOF
		{
			input = filter_out_comment(input); // Remove comments from input
			if (input == NULL) // If filtering failed, continue to next iteration
				continue;

			// Check for syntax errors in the input
			if (syntax_error(s_datas, input) == 1)
			{
				s_datas->status = 2; // Set status for syntax error
				free(input); // Free the input buffer
				continue; // Continue to the next iteration
			}
			input = swap_variable(input, s_datas); // Swap any variables in input
			loop_status = tokenize_commands(s_datas, input); // Tokenize and execute commands
			s_datas->counter += 1; // Increment process counter
			free(input); // Free the input buffer
		}
		else // EOF detected
		{
			loop_status = 0; // Exit the loop
			free(input); // Free the input buffer
		}
	}
}

