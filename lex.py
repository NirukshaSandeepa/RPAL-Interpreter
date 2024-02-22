def analyze(input_string):
    tokens = []
    while input_string:
        # Match and consume Spaces rule
        spaces_count = 0
        while input_string and input_string[0] in (' ', '\t', '\n'):
            spaces_count += 1
            input_string = input_string[1:]
        
        if spaces_count:
            continue  # Skip this iteration and go to the next character
        
        input_string = input_string.lstrip()  # Remove leading whitespace
        
        if input_string.startswith("//"):  # Check for comments
            input_string = input_string[input_string.find("\n")+1:]  # Skip the comment
        elif input_string.startswith("'"):  # Check for string literals with single quotes
            end_index = input_string[1:].find("'")
            if end_index == -1:
                raise ValueError("Invalid string format")
            tokens.append(('STRING', input_string[:end_index+2]))  # Add string literal token
            input_string = input_string[end_index+2:]  # Move past the string literal
        elif input_string[0] in ('(', ')', ';', ','):
            tokens.append(('PUNCTION', input_string[0]))  # Add punctuation token
            input_string = input_string[1:]  # Move past the punctuation
        elif input_string[0].isalpha() or input_string[0] == '_':  # Check for identifiers
            identifier = ''
            while input_string and (input_string[0].isalnum() or input_string[0] == '_'):
                identifier += input_string[0]
                input_string = input_string[1:]
            tokens.append(('IDENTIFIER', identifier))  # Add identifier token
        elif input_string[0].isdigit():  # Check for integers
            integer = ''
            while input_string and input_string[0].isdigit():
                integer += input_string[0]
                input_string = input_string[1:]
            tokens.append(('INTEGER', integer))  # Add integer token
        elif input_string[0] in ('+', '-', '*', '<', '>', '&', '.', '@', '/', ':', '=', '˜', '|', '$', '!', '#', '%',
                                 'ˆ', '_', '[', ']', '{', '}', '"', '‘', '?'):  # Check for operators
            operator = ''
            while input_string and input_string[0] in ('+', '-', '*', '<', '>', '&', '.', '@', '/',
                                                       ':', '=', '˜', '|', '$', '!', '#', '%',
                                                       'ˆ', '_', '[', ']', '{', '}', '"', '‘', '?'):
                operator += input_string[0]
                input_string = input_string[1:]
            tokens.append(('OPERATOR', operator))  # Add operator token
        else:
            raise ValueError("Invalid token")  # If none of the above patterns match, raise an error
    return tokens

# Example usage:
input_string = """
x := 'Hello, World!\n';
y := 'RPAL';
print(x + y);
"""
tokens = analyze(input_string)
print(tokens)
