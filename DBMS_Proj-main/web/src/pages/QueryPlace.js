import * as React from 'react';
import CssBaseline from '@mui/material/CssBaseline';
import AppBar from '@mui/material/AppBar';
import Box from '@mui/material/Box';
import Container from '@mui/material/Container';
import Toolbar from '@mui/material/Toolbar';
import Paper from '@mui/material/Paper';
import Stepper from '@mui/material/Stepper';
import Step from '@mui/material/Step';
import StepLabel from '@mui/material/StepLabel';
import Button from '@mui/material/Button';
import Typography from '@mui/material/Typography';
import { createTheme, ThemeProvider } from '@mui/material/styles';
import TableContainer from '@mui/material/TableContainer';
import Table from '@mui/material/Table';
import TableHead from '@mui/material/TableHead';
import TableRow from '@mui/material/TableRow';
import TableCell from '@mui/material/TableCell';
import TableBody from '@mui/material/TableBody';
import QueryForm from './queryPlaceComponents/QueryForm';
import Review from './queryPlaceComponents/Review';

const originalRows = [
  { name: "",identity_card_id: "", address:"", time: "" },
];
let ID = "";
let status = "";
const url = "https://cnr.ebg.tw/api/queryPlace"



const steps = ['查詢資料', '資料確認'];

function getStepContent(step) {
  switch (step) {
    case 0:
      return <QueryForm />;
    case 1:
      return <Review />;
    default:
      throw new Error('Unknown step');
  }
}

const theme = createTheme();

function App() {
  const [complete_message, setMessage] = React.useState("")
  const [rows, setRows] = React.useState(originalRows);
  const requestSearch = (searchedVal) => {
    console.log("Request Body: " + searchedVal);
    fetch(url, {
      method: 'POST',
      headers: { 'Content-Type': 'application/json'},
      body: JSON.stringify({phone_number: searchedVal})
    })
    .then(response => {
      return response.json();
    })
    .then(result => {
      if(result.success) {
        console.log(result);
        return result.data;
      }
      else {
        return result.error;
      }
    })
    .then(data => {
      console.log(typeof data + data);
      if(typeof data === 'string') {
        status = "查詢失敗，電話有誤";
        const filteredRows = [];
        setRows(filteredRows);
      }
      else {
        status = "查詢成功";
        const filteredRows = data;
        setRows(filteredRows);
      }
    })
    .catch(err => {
      console.log(err);
    })
  };

  const [activeStep, setActiveStep] = React.useState(0);

  const handleNext = () => {
    if(activeStep === steps.length - 2) {
      ID = document.getElementById("ID").value;
    }
    else if(activeStep === steps.length - 1) {
      requestSearch(ID)
    }
    setActiveStep(activeStep + 1);
  };

  const handleBack = () => {
    setActiveStep(activeStep - 1);
  };

  return (
    <ThemeProvider theme={theme}>
      <CssBaseline />
      <AppBar
        position="absolute"
        color="default"
        elevation={0}
        sx={{
          position: 'relative',
          borderBottom: (t) => `1px solid ${t.palette.divider}`,
        }}
      >
        <Toolbar>
          <Typography variant="h6" color="inherit" noWrap>
            實聯登記系統 - 店家查詢
          </Typography>
        </Toolbar>
      </AppBar>
      <Container component="main" maxWidth="sm" sx={{ mb: 4 }}>
        <Paper variant="outlined" sx={{ my: { xs: 3, md: 6 }, p: { xs: 2, md: 3 } }}>
          <Typography component="h1" variant="h4" align="center">
          店家查詢
          </Typography>
          <Stepper activeStep={activeStep} sx={{ pt: 3, pb: 5 }}>
            {steps.map((label) => (
              <Step key={label}>
                <StepLabel>{label}</StepLabel>
              </Step>
            ))}
          </Stepper>
          <React.Fragment>
            {activeStep === steps.length ? (
              <React.Fragment>
                { <Typography variant="h5" gutterBottom>
                  {status}
                   {<br/>}
                  <a href="./home">再次查詢?</a>
                </Typography> }
                <TableContainer style={{ maxHeight: 400 }}>
                  <Table stickyHeader className={theme.table} aria-label="simple table">
                    <TableHead>
                      <TableRow>
                        <TableCell>場所ID</TableCell>                      
                        <TableCell align="right">場所名稱</TableCell>
                        <TableCell align="right">場所地址</TableCell>
                        <TableCell align="right">場所電話</TableCell>
                        
                      </TableRow>
                    </TableHead>
                    <TableBody>
                      {rows.map((row) => (
                        <TableRow key={row.id}>
                          
                          <TableCell component="th" scope="row">
                            {row.place_id}
                          </TableCell>
                          <TableCell align="right">{row.name}</TableCell>
                          <TableCell align="right">{row.address}</TableCell>
                          <TableCell align="right">{row.phone_number}</TableCell>
 
                        </TableRow>
                      ))}
                    </TableBody>
                  </Table>
                </TableContainer>
              </React.Fragment>
            ) : (
              <React.Fragment>
                {getStepContent(activeStep)}
                <Box sx={{ display: 'flex', justifyContent: 'flex-end' }}>
                  {activeStep !== 0 && (
                    <Button onClick={handleBack} sx={{ mt: 3, ml: 1 }}>
                      上一步
                    </Button>
                  )}

                  <Button
                    variant="contained"
                    onClick={handleNext}
                    sx={{ mt: 3, ml: 1 }}
                  >
                    {activeStep === steps.length - 1 ? '完成' : '下一步'}
                  </Button>
                </Box>
              </React.Fragment>
            )}
          </React.Fragment>
        </Paper>
        <a href="./home">Home page</a>
      </Container>
    </ThemeProvider>
  );
}

export default App;
