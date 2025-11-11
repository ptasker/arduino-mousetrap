#!/usr/bin/env python3

import os
import re

def generate_config():
    """Generate config.h from .env file"""
    
    if not os.path.exists('.env'):
        print("Error: .env file not found!")
        return False
    
    print("Generating config.h from .env...")
    
    # Read .env file
    with open('.env', 'r') as f:
        lines = f.readlines()
    
    # Start config.h content
    config_content = """#ifndef CONFIG_H
#define CONFIG_H

// Auto-generated from .env file - DO NOT EDIT MANUALLY
// Run ./generate_config.py to update this file

"""
    
    # Parse each line
    for line in lines:
        line = line.strip()
        
        # Skip empty lines and comments
        if not line or line.startswith('#'):
            continue
        
        # Parse key=value pairs
        if '=' in line:
            key, value = line.split('=', 1)
            
            # Remove inline comments
            if '#' in value:
                value = value.split('#')[0].strip()
            
            # Remove quotes if present
            value = value.strip().strip('"').strip("'")
            key = key.strip()
            
            # Add to config
            config_content += f'const char* {key} = "{value}";\n'
    
    # End config.h content
    config_content += """
#endif
"""
    
    # Write config.h file
    with open('config.h', 'w') as f:
        f.write(config_content)
    
    print("config.h generated successfully!")
    return True

if __name__ == "__main__":
    generate_config()