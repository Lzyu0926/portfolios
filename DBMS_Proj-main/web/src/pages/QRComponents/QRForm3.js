import * as React from 'react';
import Grid from '@mui/material/Grid';
import Typography from '@mui/material/Typography';
import place3 from './place3.jpg';

export default function AddressForm() {
  return (
    <React.Fragment>
      <Typography variant="h6" gutterBottom>
        QR掃碼
      </Typography>
      <Grid container spacing={3}>
        <Grid item xs={12}>
         <img src={place3} alt="Background"/>
        </Grid>
      </Grid>
    </React.Fragment>
  );
}
