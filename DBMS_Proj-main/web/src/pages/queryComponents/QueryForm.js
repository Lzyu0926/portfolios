import * as React from 'react';
import Grid from '@mui/material/Grid';
import Typography from '@mui/material/Typography';
import TextField from '@mui/material/TextField';
import moment from 'moment'

const time = Date.now();
export default function AddressForm() {
  return (
    <React.Fragment>
      <Typography variant="h6" gutterBottom>
        疫調查詢
      </Typography>
      <Grid container spacing={3}>
        <Grid item xs={12}>
          <TextField
            required
            id="ID"
            name="ID"
            label="身分證字號"
            fullWidth
            variant="standard"
          />
        </Grid>
        <Grid item xl='auto' item xs='auto'>
          <Typography variant='spam' gutterBottom>查詢時間：{moment(time).format('YYYY-MM-DD HH:mm:ss')}</Typography>
        </Grid>
      </Grid>
    </React.Fragment>
  );
}