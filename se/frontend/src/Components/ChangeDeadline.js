import React, {useState} from 'react';
import Button from '@material-ui/core/Button';
import CssBaseline from '@material-ui/core/CssBaseline';
import TextField from '@material-ui/core/TextField';
import Link from '@material-ui/core/Link';
import Box from '@material-ui/core/Box';
import Typography from '@material-ui/core/Typography';
import { makeStyles } from '@material-ui/core/styles';
import Container from "@material-ui/core/Container";
import axios from "axios";
import AppBarNavigation from "./AppBarNavigation";


const useStyles = makeStyles((theme) => ({
    root: {
        height: '100vh',
    },
    image: {
        backgroundImage: 'url(https://source.unsplash.com/random)',
        backgroundRepeat: 'no-repeat',
        backgroundColor:
            theme.palette.type === 'light' ? theme.palette.grey[50] : theme.palette.grey[900],
        backgroundSize: 'cover',
        backgroundPosition: 'center',
    },
    paper: {
        width: '444px',
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
        // width: '100%', // Fix IE 11 issue.
        marginTop: theme.spacing(1),
    },
    submit: {
        margin: theme.spacing(3, 0, 2),
    },
    deadline: {
        margin: theme.spacing(3, 0, 2),
    },
    cont: {
        width: '100%',
        justifyContent: "center",
        marginLeft: '30%',
    }
}));

export default function ChangeDeadline() {

    function changeAbstractDeadline(event){
        event.preventDefault();
        event.persist();
        let id = parseInt(window.sessionStorage.getItem("conferenceId"));

        axios.defaults.baseURL= "http://localhost:8080";

        axios.post('/conferences/changeAbstractDeadline', null, {
            params: {
                id: id,
                deadline: deadline
            }
        }).then(response=>{console.log(response)})
            .catch((error) => console.log(error));

    }

    function changePaperDeadline(event){
        event.preventDefault();
        event.persist();
        let id = window.sessionStorage.getItem("conferenceId");
        axios.defaults.baseURL= "http://localhost:8080";

        axios.post('/conferences/changePaperDeadline', null, {
            params: {
                id: id,
                deadline: deadlinepaper
            }
        }).then(response=>{console.log(response)})
            .catch((error) => console.log(error));

    }

    //window.sessionStorage.setItem('userType', 'chair');

    const classes = useStyles();

    const [deadline,setDeadline] = useState("");

    const [deadlinepaper,setDeadlinepaper] = useState("");

    return (
        // eslint-disable-next-line react/jsx-no-undef
        <Container component="main" maxWidth="xl">
            <AppBarNavigation></AppBarNavigation>
            <CssBaseline />
            <Container className={classes.cont}>
            <div className={classes.paper}>
                <Typography component="h1" variant="h5">
                    Change abstract deadline
                </Typography>

                <TextField
                    onChange={e=>setDeadline(e.target.value)}
                    variant="outlined"
                    margin="normal"
                    format="dd-MM-yyyy"
                    required
                    fullWidth
                    id="deadline"
                    label="New deadline"
                    name="deadline"
                    autoComplete="deadline"
                    autoFocus
                />
                <Button
                    type="submit"
                    onClick={changeAbstractDeadline}
                    fullWidth
                    variant="contained"
                    color="primary"
                    className={classes.submit}
                >
                    Change deadline
                </Button>

                <Typography component="h1" variant="h5">
                    Change paper deadline
                </Typography>

                <TextField
                    onChange={e=>setDeadlinepaper(e.target.value)}
                    variant="outlined"
                    margin="normal"
                    format="dd-MM-yyyy"
                    required
                    fullWidth
                    id="deadlinepaper"
                    label="New paper deadline"
                    name="deadlinepaper"
                    autoComplete="deadline"
                    autoFocus
                />
                <Button
                    type="submit"
                    onClick={changePaperDeadline}
                    fullWidth
                    variant="contained"
                    color="primary"
                    className={classes.submit}
                >
                    Change paper deadline
                </Button>
            </div>
            </Container>
            <Box mt={8}>
            </Box>

        </Container>
    );
}
