const express = require('express')
const app = express()
const port = 3000

const {Client} = require('pg');
const client = new Client({
  host: 'localhost',
  user: "postgres",
  port: 5432,
  password: "mypass",
  database: "colors"
});

client.connect().then(() => {
  console.log("Connected to PostgreSQL database");
}).catch(err => {
  console.error("Connection error", err.stack);
});

// Middleware to parse JSON bodies

app.use(express.json());

app.get('/', (req, res) => {
  res.send('Hello World!')
})

app.get('/tshirt', (req, res) => {
  res.status(200).send('Test endpoint is working!')
});

app.post('/tshirt/:id', (req, res) => {
  const { id } = req.params;
  const logo = req.body;

  if (!logo) {
    return res.status(400).send('Logo is required');
  }

  res.status(201);
  res.send(`T-shirt with ID ${id} created with logo ${logo.logo} with color ${logo.color}`);

});

app.post('/colors', async (req, res) => {
  const body = req.body;
  const { id, color } = body || {};

  if (typeof id === 'undefined' || typeof color === 'undefined') {
    return res.status(400).send('Missing "id" or "color" in request body');
  }

  const parsedId = Number(id);
  if (Number.isNaN(parsedId)) {
    return res.status(400).send('"id" must be a number');
  }

  // The database table uses columns: colorid INT, colorname CHAR(20)
  // Map incoming fields -> table columns and validate length for CHAR(20)
  const colorStr = String(color);
  if (colorStr.length > 20) {
    return res.status(400).send('"color" must be at most 20 characters');
  }

  try {
    // Use a parameterized query to avoid SQL syntax errors and injection
    await client.query('INSERT INTO colors (colorid, colorname) VALUES ($1, $2)', [parsedId, colorStr]);
    return res.status(201).send(`Color ${colorStr} with ID ${parsedId} added to database`);
  } catch (err) {
    console.error('Error inserting color:', err);
    // If the error is a PostgreSQL error, include the message for easier debugging
    if (err && err.message) {
      return res.status(500).send(`Error inserting color: ${err.message}`);
    }
    return res.status(500).send('Error inserting color');
  }

});

//To do: Implement /sensors/register endpoint
app.post('/sensors/register', (req, res) => {

});

// To do: Implement /readings/upload endpoint
app.post('/readings/upload', (req, res) => {

});

// To do: Implement /readings/query endpoint
app.get('/readings/query', (req, res) => {

});

app.listen(port, () => {
  console.log(`Example app listening on port ${port}`)
})