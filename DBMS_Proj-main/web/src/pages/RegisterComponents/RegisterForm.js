import * as React from 'react';
import Grid from '@mui/material/Grid';
import Typography from '@mui/material/Typography';
import TextField from '@mui/material/TextField';
import moment from 'moment'
import {placeid} from '../RegBeenPlace'
import {phonenum} from '../RegBeenPlace'

const time = Date.now();
export default function AddressForm() {
  return (
    <React.Fragment>
      <Typography variant="h6" gutterBottom>
        疫調登記
      </Typography>
      <Grid container spacing={3}>
        <Grid item xs={12}>
          <TextField
            required
            id="PlaceID"
            name="PlaceID"
            label="場所代碼"
            fullWidth
            variant="standard"
            value={placeid}
            onChange={(e)=>{placeid=e.target.value}}
          />
        </Grid>
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
        <Grid item xl='auto' item xs='auto'>
          <Typography variant='spam' gutterBottom>登記時間：{moment(time).format('YYYY-MM-DD HH:mm:ss')}</Typography>
        </Grid>
      </Grid>
    </React.Fragment>
  );
}
