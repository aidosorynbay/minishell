int error_syntaxcheck(t_token **tokens)
{
    perror("exit: 258 syntax error near unexpected token `|'");
	token_clear(tokens);
    return (1);
}