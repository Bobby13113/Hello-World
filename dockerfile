# Use official Node.js LTS image
FROM node:20-alpine

# Set working directory
WORKDIR /app

# Copy package.json and install dependencies
COPY package.json ./
RUN npm install

# Copy application code
COPY . .

# Expose port 8081
EXPOSE 8081

# Start the app
CMD ["node", "index.js"]