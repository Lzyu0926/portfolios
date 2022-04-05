import * as React from 'react';
import { Link } from 'react-router-dom'
import CssBaseline from '@mui/material/CssBaseline';
import AppBar from '@mui/material/AppBar';
import Container from '@mui/material/Container';
import Toolbar from '@mui/material/Toolbar';
import Button from '@mui/material/Button';
import Typography from '@mui/material/Typography';
import { createTheme, ThemeProvider } from '@mui/material/styles';
import Card from '@mui/material/Card';
import CardActions from '@mui/material/CardActions';
import CardHeader from '@mui/material/CardHeader';
import Grid from '@mui/material/Grid';

const theme = createTheme();

function App() {
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
            實聯登記系統 - Home Page
          </Typography>
        </Toolbar>
      </AppBar>
      <Container sx={{ my: 3 }} maxWidth="xl" >
        <Typography component="h1" variant="h4" align="center">
          Home Page
        </Typography>
        <Container maxWidth="xl" component="main">
          <Grid container sx={{ maxWidth: '100%', mt: 2 }} justifyContent="center " spacing={2}>
            <Grid item sm={8} md={6} lg={3} xl={3} sx={{ my: 4 }}>
              <Card>
                <CardHeader
                  title="身分證註冊"
                  titleTypographyProps={{ align: 'center' }}
                  sx={{ py: 4, color: '#FFF', backgroundColor: '#2F6388' }}
                />
                <CardActions>
                  <Button sx={{ py: 1 }} href="/people" fullWidth variant="contained">
                      前往註冊
                  </Button>
                </CardActions>
              </Card>
            </Grid>
            <Grid item sm={8} md={6} lg={3} xl={3} sx={{ my: 4 }}>
              <Card>
                <CardHeader
                  title="手機註冊"
                  titleTypographyProps={{ align: 'center' }}
                  sx={{ py: 4, color: '#FFF', backgroundColor: '#2F8377' }}
                />
                <CardActions>
                  <Button sx={{ py: 1 }} href="/phone" fullWidth variant="contained">
                      前往註冊
                  </Button>
                </CardActions>
              </Card>
            </Grid>
            <Grid item sm={8} md={6} lg={3} xl={3} sx={{ my: 4 }}>
              <Card>
                <CardHeader
                  title="場所登記"
                  titleTypographyProps={{ align: 'center' }}
                  sx={{ py: 4, color: '#FFF', backgroundColor: '#C84C47' }}
                />
                <CardActions>
                  <Button sx={{ py: 1 }} href="/address" fullWidth variant="contained">
                      前往登記
                  </Button>
                </CardActions>
              </Card>
            </Grid>
            <Grid item sm={8} md={6} lg={3} xl={3} sx={{ my: 4 }}>
              <Card>
                <CardHeader
                  title="實聯登記"
                  titleTypographyProps={{ align: 'center' }}
                  sx={{ py: 4, color: '#FFF', backgroundColor: '#B3590F' }}
                />
                <CardActions>
                  <Button sx={{ py: 1 }} href="/reg" fullWidth variant="contained">
                      前往登記
                  </Button>
                </CardActions>
              </Card>
            </Grid>
            <Grid item sm={8} md={6} lg={3} xl={3} sx={{ my: 4 }}>
              <Card>
                <CardHeader
                  title="疫調查詢"
                  titleTypographyProps={{ align: 'center' }}
                  sx={{ py: 4, color: '#FFF', backgroundColor: '#00A65A' }}
                />
                <CardActions>
                  <Button sx={{ py: 1 }} href="/query" fullWidth variant="contained">
                      前往查詢
                  </Button>
                </CardActions>
              </Card>
            </Grid>
            <Grid item sm={8} md={6} lg={3} xl={3} sx={{ my: 4 }}>
              <Card>
                <CardHeader
                  title="店家查詢"
                  titleTypographyProps={{ align: 'center' }}
                  sx={{ py: 4, color: '#FFF', backgroundColor: '#50BFE6' }}
                />
                <CardActions>
                  <Button sx={{ py: 1 }} href="/queryplace" fullWidth variant="contained">
                      前往查詢
                  </Button>
                </CardActions>
              </Card>
            </Grid>
            <Grid item sm={8} md={6} lg={3} xl={3} sx={{ my: 4 }}>
              <Card>
                <CardHeader
                  title="QR查詢"
                  titleTypographyProps={{ align: 'center' }}
                  sx={{ py: 4, color: '#FFF', backgroundColor: '#DDA0DD' }}
                />
                <CardActions>
                  <Button sx={{ py: 1 }} href="/qr" fullWidth variant="contained">
                      前往查詢
                  </Button>
                </CardActions>
              </Card>
            </Grid>
          </Grid>
        </Container>
      </Container >
    </ThemeProvider >
    // <div>
    //   <a href="./address">SignUpAddress page</a>
    //   <a href="./phone">SignUpPhone page</a>
    //   <a href="./query">QueryPhone page</a>
    //   <a href="./reg">RegBeenPlace page</a>
    //   <a href="./home">Home page</a>
    // </div>
  );
}

export default App;
