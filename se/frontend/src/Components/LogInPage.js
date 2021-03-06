import React, {useState} from 'react';
import Avatar from '@material-ui/core/Avatar';
import Button from '@material-ui/core/Button';
import CssBaseline from '@material-ui/core/CssBaseline';
import TextField from '@material-ui/core/TextField';
import FormControlLabel from '@material-ui/core/FormControlLabel';
import Checkbox from '@material-ui/core/Checkbox';
import Link from '@material-ui/core/Link';
import Paper from '@material-ui/core/Paper';
import Box from '@material-ui/core/Box';
import Grid from '@material-ui/core/Grid';
import LockOutlinedIcon from '@material-ui/icons/LockOutlined';
import Typography from '@material-ui/core/Typography';
import {makeStyles} from '@material-ui/core/styles';
import axios from 'axios';
import AppBarNavigation from './AppBarNavigation';



const useStyles = makeStyles((theme) => ({
    root: {
        height: '100vh',
    },
    image: {
        backgroundImage: 'url(https://media.nurse.org/cache/54/20/5420b866c560824ffa5e3fca257bdf60@2x.jpg)',
        backgroundRepeat: 'no-repeat',
        backgroundColor:
            theme.palette.type === 'light' ? theme.palette.grey[50] : theme.palette.grey[900],
        backgroundSize: 'cover',
        backgroundPosition: 'center',
    },
    paper: {
        margin: theme.spacing(8, 4),
        display: 'flex',
        flexDirection: 'column',
        alignItems: 'center',
    },
    avatar: {
        margin: theme.spacing(1),
        backgroundColor: theme.palette.secondary.main,
    },
    form: {
        width: '100%', // Fix IE 11 issue.
        marginTop: theme.spacing(1),
    },
    submit: {
        margin: theme.spacing(3, 0, 2),
    },
}));

export default function LogInPage() {

    const classes = useStyles();
    const [email,setEmail] = useState("");
    const [password,setPassword] = useState("");

    function login(event){
        event.preventDefault();
        axios.defaults.baseURL = "http://localhost:8080";
        axios.get('/author/login', {params: {
            email:email,
            password:password
        }}).then(r => {
            let data = r.data;
            if (data !== "") {
                window.sessionStorage.setItem("userId", data['userId']);
                window.sessionStorage.setItem("conferenceId", data['conferenceId']);
                window.sessionStorage.setItem("userType", "author");
                window.location = "/submitMetaInfo";
            }
        });
        axios.get('/listener/login', {params: {
                email:email,
                password:password
            }}).then(r => {
            let data = r.data;
            if (data !== "") {
                window.sessionStorage.setItem("userId", data['userId']);
                window.sessionStorage.setItem("conferenceId", data['conferenceId']);
                window.sessionStorage.setItem("userType", "listener");
                window.location = "/";
            }
        });
        axios.get('/pcmembers/login', {params: {
                email:email,
                password:password
            }}).then(r => {
            let data = r.data;
            if (data !== "") {
                window.sessionStorage.setItem("userId", data['userId']);
                window.sessionStorage.setItem("conferenceId", data['conferenceId']);
                window.sessionStorage.setItem("userType", "pcmember");
                window.location = "/bidding";
            }
        });
        axios.get('/chairs/login', {params: {
                email:email,
                password:password
            }}).then(r => {
            let data = r.data;
            if (data !== "") {
                window.sessionStorage.setItem("userId", data['userId']);
                window.sessionStorage.setItem("conferenceId", data['conferenceId']);
                window.sessionStorage.setItem("userType", "chair");
                window.location = "/changeDeadline";
            }
        });
        axios.get('/steering/login', {params: {
                email:email,
                password:password
            }}).then(r => {
            let data = r.data;
            if (data !== "") {
                window.sessionStorage.setItem("userId", data['userId']);
                window.sessionStorage.setItem("conferenceId", data['conferenceId']);
                window.sessionStorage.setItem("userType", "steering");
                window.location = "/conferenceCreation";
            }
        });

    }


    return (
        <div>
            <AppBarNavigation></AppBarNavigation>
        <Grid container component="main" className={classes.root}>
            <CssBaseline />
            <Grid item xs={false} sm={4} md={7} className={classes.image} />
            <Grid item xs={12} sm={8} md={5} component={Paper} elevation={6} square>
                <div className={classes.paper}>
                    <Avatar className={classes.avatar}>
                        <LockOutlinedIcon />
                    </Avatar>
                    <Typography component="h1" variant="h5">
                        Log In
                    </Typography>
                    <form className={classes.form} noValidate>
                        <TextField
                            variant="outlined"
                            margin="normal"
                            required
                            fullWidth
                            id="email"
                            label="Email Address"
                            name="email"
                            autoComplete="email"
                            autoFocus
                            onChange={e=>setEmail(e.target.value)}
                        />
                        <TextField
                            variant="outlined"
                            margin="normal"
                            required
                            fullWidth
                            name="password"
                            label="Password"
                            type="password"
                            id="password"
                            autoComplete="current-password"
                            onChange={e=>setPassword(e.target.value)}

                        />
                       
                        <Button
                            type="submit"
                            fullWidth
                            variant="contained"
                            color="primary"
                            className={classes.submit}
                            onClick={e=>login(e)}
                        >
                            Log In
                        </Button>
                        <Grid container>
                            <Grid item>
                                <Link href="/signUp" variant="body2">
                                    {"Don't have an account? Sign Up"}
                                </Link>
                            </Grid>
                        </Grid>
                      
                    </form>
                </div>
            </Grid>
        </Grid>
        </div>
    );
}
