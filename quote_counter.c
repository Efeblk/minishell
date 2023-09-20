int quote_counter(char *str)
{
    int i;
    int quote_count;

    i = 0;
    quote_count = 0;
    while (str[i])
    {
        if (str[i] == '"' || str[i] == '\'')
            quote_count++;
        i++;
    }
    return (quote_count);
}