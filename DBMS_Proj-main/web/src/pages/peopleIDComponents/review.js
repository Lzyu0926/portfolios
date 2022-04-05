import * as React from 'react';
import Typography from '@mui/material/Typography';
import Grid from '@mui/material/Grid';
import {name} from '../SignUpPeopleID'
import {peopleID} from '../SignUpPeopleID'



export default function Review() {
  return (
    <React.Fragment>
      <Typography variant="h6" gutterBottom>
        確認資料是否無誤
      </Typography>
      <Grid container spacing={2}>
        <Grid item xs={12} sm={6}>
          <Typography variant="h6" gutterBottom sx={{ mt: 2 }}>
            身份註冊
          </Typography>
          <Typography gutterBottom>姓名 </Typography>
          <Typography gutterBottom>{name}</Typography>
          <Typography gutterBottom>身分證字號</Typography>
          <Typography gutterBottom>{peopleID}</Typography>
          
        </Grid>
      </Grid>
    </React.Fragment>
  );
}
