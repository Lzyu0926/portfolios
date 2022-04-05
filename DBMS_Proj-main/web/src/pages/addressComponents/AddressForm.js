import * as React from 'react';
import Grid from '@mui/material/Grid';
import Typography from '@mui/material/Typography';
import TextField from '@mui/material/TextField';

class AddressForm extends React.Component {
  constructor(props) {
    super(props);
    this.name = ""
    this.address = ""
    this.phone_number = ""
  }

  handleName = (event) => {
    this.name = event.target.value;
    this.props.setName(this.name)
  };

  handlePhone = (event) => {
    this.phone = event.target.value//.replace(/-/g, "");
    this.props.setPhone(this.phone)
  };

  handleAddress = (event) => {
    this.address = event.target.value;
    this.props.setAddress(this.address)
  };  


  render() {

    return (
      <React.Fragment>
        <Typography variant="h6" gutterBottom>
          店家資訊
        </Typography>
        <Grid container spacing={3}>
          <Grid item xs={12}>
            <TextField
              id="storeName"
              name="storeName"
              label="店名"
              fullWidth
              variant="standard"
              onChange={this.handleName} 
            />
          </Grid>
          <Grid item xs={12}>
            <TextField
              required
              id="trailingAddress"
              name="trailingAddress"
              label="地址"
              fullWidth
              autoComplete="shipping address-level1"
              variant="standard"
              onChange={this.handleAddress} 
            />
          </Grid>
          <Grid item xs={12}>
            <TextField
              required
              id="phone_number"
              name="phone_number"
              label="電話號碼"
              fullWidth
              autoComplete="phone"
              variant="standard"
              onChange={this.handlePhone}
            />
          </Grid>
        </Grid>
      </React.Fragment>
    );
  }
}

export default AddressForm;