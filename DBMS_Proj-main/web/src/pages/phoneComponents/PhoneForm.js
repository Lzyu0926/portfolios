import * as React from 'react';
import Grid from '@mui/material/Grid';
import Typography from '@mui/material/Typography';
import TextField from '@mui/material/TextField';

export default function PhoneForm() {
  return (
    <React.Fragment>
      <Typography variant="h6" gutterBottom>
        身分證字號
      </Typography>
      <Grid container spacing={3}>
        <Grid item xs={12}>
          <TextField
            required
            id="PeopleID"
            name="PeopleID"
            label="身分證字號"
            fullWidth
            variant="standard"
          />
        </Grid>
      </Grid>
      <br/>
      <Typography variant="h6" gutterBottom>
        手機登記
      </Typography>
      <Grid container spacing={3}>
        <Grid item xs={12}>
          <TextField
            required
            id="PhoneNum"
            name="PhoneNum"
            label="手機號碼"
            fullWidth
            variant="standard"
          />
        </Grid>
      </Grid>
    </React.Fragment>
  );
}
