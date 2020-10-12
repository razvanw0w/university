import React, {useState} from 'react';
import Avatar from '@material-ui/core/Avatar';
import Button from '@material-ui/core/Button';
import CssBaseline from '@material-ui/core/CssBaseline';
import TextField from '@material-ui/core/TextField';
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
            backgroundImage: 'url(https://boardroom.global/wp-content/uploads/2019/11/Hangzhou–Leading-Innovation-for-Future-Conferences-e1573117529871.jpg)',
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


function validateEmail(email) {
    /*
    Source: https://stackoverflow.com/questions/46155/how-to-validate-an-email-address-in-javascript
     */
    const re = /^(([^<>()\[\]\\.,;:\s@"]+(\.[^<>()\[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;
    return re.test(String(email).toLowerCase());
}

function validateWebpage(webpage){
    /*
    Validates the following formats.
    Source : https://stackoverflow.com/questions/161738/what-is-the-best-regular-expression-to-check-if-a-string-is-a-valid-url

    www.google.com
    http://www.google.com
    mailto:somebody@google.com
    somebody@google.com
    www.url-with-querystring.com/?url=has-querystring

     */
    const re = /((([A-Za-z]{3,9}:(?:\/\/)?)(?:[-;:&=\+\$,\w]+@)?[A-Za-z0-9.-]+|(?:www.|[-;:&=\+\$,\w]+@)[A-Za-z0-9.-]+)((?:\/[\+~%\/.\w-_]*)?\??(?:[-\+=&;%@.\w_]*)#?(?:[\w]*))?)/;
    return re.test(String(webpage).toLowerCase());
}

    export default function SignUpPage() {

        function submitData(event){
            event.preventDefault();
            event.persist();
            axios.defaults.baseURL = "http://localhost:8080";
            if(!validateEmail(email)){
                console.log("Wrong Email");
                alert("That is not a valid email");
                return;
            }
            if(!validateWebpage(webpage)){
                console.log("Invalid Webpage");
                alert("That is not a valid webpage");
                return;
            }

            if(code==="")
            {
                console.log("here");

                axios.post('/steering/add',null,{ params: {
                            name: name,
                            affiliation: affiliation,
                            email: email.toLowerCase(),
                            webpage: webpage,
                            username: username,
                            password: password
                        }
                    }
                ).then((response)=>{console.log(response.data);
                    window.location = "/logIn";
                });
            }
            else {
                axios.get("/conferences/code", {
                    params: {cod: code}
                }).then(r => {
                    let codeResp = r.data[0];

                    if (codeResp === "author") {

                        axios.post("/author/add", null, {
                            params: {
                                conferenceId: r.data[1],
                                name: name,
                                affiliation: affiliation,
                                email: email,
                                webpage: webpage,
                                username: username,
                                password: password
                            }
                        }).then(response => {
                            console.log(response);
                            window.location = "/logIn";
                        });

                    }
                    if (codeResp === "chair") {
                        axios.post("/chairs/add", null, {
                            params: {
                                conferenceId: r.data[1],
                                name: name,
                                affiliation: affiliation,
                                email: email,
                                webpage: webpage,
                                username: username,
                                password: password
                            }
                        }).then(response => {
                            console.log(response);
                            window.location = "/logIn";
                        });
                    }
                    if (codeResp === "pcmember") {
                        axios.post("/pcmembers/add", null, {
                            params: {
                                conferenceId: r.data[1],
                                name: name,
                                affiliation: affiliation,
                                email: email,
                                webpage: webpage,
                                username: username,
                                password: password
                            }
                        }).then(response => {
                            console.log(response);
                            window.location = "/logIn";
                        });

                    }
                    if (codeResp === "listener") {
                        axios.post("/listener/add", null, {
                            params: {
                                conferenceId: r.data[1],
                                name: name,
                                affiliation: affiliation,
                                email: email,
                                webpage: webpage,
                                username: username,
                                password: password
                            }
                        }).then(response => {
                            console.log(response);
                            window.location = "/logIn";
                        });

                    }
                });
            }
            

        }

        const classes = useStyles();


        //setters and getters (email is the field, set email is the setter)
        // This allows for a lil' more functional perspective
        const [email,setEmail] = useState("");
        const [password,setPassword] = useState("");
        const [name, setName] = useState("");
        const [affiliation, setAffiliation] = useState("");
        const [username, setUsername] = useState("");
        const [webpage, setWebpage] = useState("");
        const [code, setCode] = useState("");

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
                            Sign up
                        </Typography>
                        <form className={classes.form} noValidate>
                            <TextField
                                onChange={e=>setName(e.target.value)}
                                variant="outlined"
                                margin="normal"
                                required
                                fullWidth
                                id="name"
                                label="Full name "
                                name="name"
                                autoComplete="name"
                                autoFocus
                            />
                            <TextField
                                onChange={e=>setAffiliation(e.target.value)}
                                variant="outlined"
                                margin="normal"
                                required
                                fullWidth
                                id="affiliation"
                                label="Affiliation"
                                name="affiliation"
                                autoComplete="affiliation"
                                autoFocus
                            />
                            <TextField
                                onChange={e=>setEmail(e.target.value)}
                                variant="outlined"
                                margin="normal"
                                required
                                fullWidth
                                id="email"
                                label="Email Address"
                                name="email"
                                autoComplete="email"
                                autoFocus
                            />
                            <TextField
                                onChange={e=>setWebpage(e.target.value)}
                                variant="outlined"
                                margin="normal"
                                required
                                fullWidth
                                id="webpage"
                                label="Webpage"
                                name="webpage"
                                autoComplete="webpage"
                                autoFocus
                            />
                            <TextField
                                onChange={e=>setUsername(e.target.value)}
                                variant="outlined"
                                margin="normal"
                                required
                                fullWidth
                                id="username"
                                label="Username"
                                name="username"
                                autoComplete="username"
                                autoFocus
                            />
                            <TextField
                                onChange={e=>setPassword(e.target.value)}
                                variant="outlined"
                                margin="normal"
                                required
                                fullWidth
                                name="password"
                                label="Password"
                                type="password"
                                id="password"
                                autoComplete="current-password"
                            />
                            <TextField
                                onChange={e=>setCode(e.target.value)}
                                variant="outlined"
                                margin="normal"
                                fullWidth
                                name="code"
                                label="Code"
                                type="code"
                                id="code"
                                autoComplete="code"
                            />
                            <Button
                                onClick={submitData}
                                type="submit"
                                fullWidth
                                variant="contained"
                                color="primary"
                                className={classes.submit}
                            >
                                Sign Up
                            </Button>
                        </form>
                    </div>
                </Grid>
            </Grid>
            </div>
        );
    }
