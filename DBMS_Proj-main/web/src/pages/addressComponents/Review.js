import * as React from 'react';
import Typography from '@mui/material/Typography';
import Grid from '@mui/material/Grid';

class Review extends React.Component {
  render() {
    return (
      <React.Fragment>
        <Typography variant="h6" gutterBottom>
          確認資料是否無誤
        </Typography>
        <Grid container spacing={2}>
          <Grid item xs={6} sm={6}>
            <Typography variant="h6" gutterBottom sx={{ mt: 2 }}>
              店家資訊
            </Typography>
            <Typography gutterBottom>{this.props.name}</Typography>
            <Typography gutterBottom>{this.props.address}</Typography>
          </Grid>
          <Grid item xs={6} sm={6}>
            <Typography variant="h6" gutterBottom sx={{ mt: 2 }}>
              負責人資訊
            </Typography>
            <Typography gutterBottom>電話號碼: {this.props.phone}</Typography>
          </Grid>
        </Grid>
      </React.Fragment>
    );
  }
}

export default Review;