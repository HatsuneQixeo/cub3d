#!/bin/bash

# Define a heredoc with ANSI color codes
read -r -d '' MESSAGE << EOM
\033[0;31mError:\033[0m Something went wrong.
\033[0;32mSuccess:\033[0m Everything is OK.
EOM

# Print the heredoc with color codes
echo -e "$MESSAGE"