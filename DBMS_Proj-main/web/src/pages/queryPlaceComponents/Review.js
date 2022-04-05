import * as React from 'react';
import {ID} from '../QueryPhone';
import Typography from '@mui/material/Typography';
import Grid from '@mui/material/Grid';

// let ID='';

export default function Review() {
  return (
    <React.Fragment>
      <Typography variant="h6" gutterBottom>
        確認資料是否無誤
      </Typography>
      <Grid container spacing={2}>
        <Grid item xs={12} sm={6}>
          <Typography variant="h6" gutterBottom sx={{ mt: 2 }}>
            店家查詢
          </Typography>
          <Typography gutterBottom>店家電話 </Typography>
          <Typography gutterBottom>{ID}</Typography>
        </Grid>
      </Grid>
    </React.Fragment>
  );
}
