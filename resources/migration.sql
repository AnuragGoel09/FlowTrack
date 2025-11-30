CREATE TABLE IF NOT EXISTS commits (
  commitHash TEXT PRIMARY KEY,
  branch TEXT,
  message TEXT,
  author TEXT,
  timestamp TEXT,
  processedAt TEXT
);
