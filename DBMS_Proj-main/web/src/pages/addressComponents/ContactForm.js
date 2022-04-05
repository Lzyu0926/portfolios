import * as React from 'react';
import Typography from '@mui/material/Typography';
import Grid from '@mui/material/Grid';
import TextField from '@mui/material/TextField';

export default function ContactForm() {
  return (
    <React.Fragment>
      <Typography variant="h6" gutterBottom>
        負責人聯絡方式
      </Typography>
      <Grid container spacing={3}>
        <Grid item xs={12} >
          <TextField
            required
            id="concatName"
            name="concatName"
            label="聯絡人全名"
            fullWidth
            autoComplete="name"
            variant="standard"
          />
        </Grid>
        <Grid item xs={12} >
          <TextField
            required
            id="phoneNumber"
            name="phoneNumber"
            label="電話號碼"
            fullWidth
            autoComplete="tel"
            variant="standard"
          />
        </Grid>
      </Grid>
    </React.Fragment>
  );
}
