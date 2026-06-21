import { defineConfig } from 'astro/config';
import node from '@astrojs/node';

export default defineConfig({
  // Changes Astro from building flat HTML files to running a live dynamic server
  output: 'server',
  adapter: node({
    mode: 'standalone',
  }),
});