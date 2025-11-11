#!/bin/bash

# Script to generate config.h from .env file
# Usage: ./generate_config.sh

echo "Generating config.h from .env..."

# Check if .env exists
if [ ! -f ".env" ]; then
    echo "Error: .env file not found!"
    exit 1
fi

# Start config.h file
cat > config.h << 'EOF'
#ifndef CONFIG_H
#define CONFIG_H

// Auto-generated from .env file - DO NOT EDIT MANUALLY
// Run ./generate_config.sh to update this file

EOF

# Parse .env and convert to C++ constants
while IFS= read -r line; do
    # Skip empty lines and comment lines
    if [[ -z "$line" || "$line" =~ ^[[:space:]]*# ]]; then
        continue
    fi
    
    # Extract key and value
    if [[ "$line" =~ ^([^=]+)=(.*)$ ]]; then
        key="${BASH_REMATCH[1]}"
        value="${BASH_REMATCH[2]}"
        
        # Remove comments from value
        value=$(echo "$value" | sed 's/[[:space:]]*#.*//')
        
        # Remove surrounding quotes if present
        value=$(echo "$value" | sed 's/^["'\'']//' | sed 's/["'\'']$//')
        
        # Trim whitespace
        key=$(echo "$key" | xargs)
        value=$(echo "$value" | xargs)
        
        # Convert to C++ constant
        echo "const char* $key = \"$value\";" >> config.h
    fi
    
done < .env

# End config.h file
cat >> config.h << 'EOF'

#endif
EOF

echo "config.h generated successfully!"