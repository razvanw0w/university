import React, {useState} from 'react';
import Avatar from '@material-ui/core/Avatar';
import Button from '@material-ui/core/Button';
import CssBaseline from '@material-ui/core/CssBaseline';
import TextField from '@material-ui/core/TextField';
import Paper from '@material-ui/core/Paper';
import Grid from '@material-ui/core/Grid';
import AssignmentIcon from '@material-ui/icons/Assignment';
import Typography from '@material-ui/core/Typography';
import {KeyboardDatePicker, MuiPickersUtilsProvider} from '@material-ui/pickers'
import {makeStyles} from '@material-ui/core/styles';
import DateFnsUtils from "@date-io/date-fns";
import axios from 'axios';
import Dialog from "@material-ui/core/Dialog";
import DialogTitle from "@material-ui/core/DialogTitle";
import DialogContent from "@material-ui/core/DialogContent";
import DialogActions from "@material-ui/core/DialogActions";
import DialogContentText from "@material-ui/core/DialogContentText";
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
        width: '50%', // Fix IE 11 issue.
        marginTop: theme.spacing(1),
    },
    submit: {
        margin: theme.spacing(3, 0, 2),
    },
}));

export default function CreateConferencePage() {
    function submitConference(event) {
        event.preventDefault();
        console.log(buildDateString(abstractDeadline))
        console.log(buildDateString(paperDeadline))
        console.log(buildDateString(startTime))
        console.log(buildDateString(endTime))
        axios.defaults.baseURL = "http://localhost:8080";
        axios.post(
            '/conferences/add', null, {
                params: {
                    name: name,
                    fee: fee,
                    abstractDeadline: buildDateString(abstractDeadline),
                    paperDeadline: buildDateString(paperDeadline),
                    startTime: buildDateString(startTime),
                    endTime: buildDateString(endTime),
                    chairCode: chairCode,
                    PCMemberCode: PCMemberCode,
                    authorCode: authorCode,
                    listenerCode: listenerCode,
                    userId: window.sessionStorage.getItem("userId")
                }
            })
            .then((response) => window.sessionStorage.setItem("conferenceId", response.data))
            .catch((error) => console.log(error))
    }

    function buildDateString(date) {
        console.log(date.getDate());
        console.log(date.getMonth() + 1);
        console.log(date.getFullYear());
        let day = date.getDate();
        let month = date.getMonth() + 1;
        let year = date.getFullYear();
        return `${day}-${month}-${year}`;
    }

    const classes = useStyles();
    const [name, setName] = useState("");
    const [fee, setFee] = useState("");
    const [abstractDeadline, setAbstractDeadline] = useState(new Date());
    const [paperDeadline, setPaperDeadline] = useState(new Date());
    const [startTime, setStartTime] = useState(new Date());
    const [endTime, setEndTime] = useState(new Date());
    const [chairCode, setChairCode] = useState("");
    const [PCMemberCode, setPCMemberCode] = useState("");
    const [authorCode, setAuthorCode] = useState("");
    const [listenerCode, setListenerCode] = useState("");
    const [confirming, setConfirming] = useState(false);

    const handleConfirmOpen = (event) => {
        event.preventDefault();
        console.log("opened");
        setConfirming(true);
    };

    const handleConfirmClose = (event) => {
        event.preventDefault();
        console.log("closed");
        setConfirming(false);
    };

    const handleConfirmAgree = (event) => {
        submitConference(event);
        handleConfirmClose(event);
    }

    const handleNameChange = (newName) => {
        setName(newName);
        setChairCode(`${newName}#Chair`);
        setPCMemberCode(`${newName}#PCM`);
        setAuthorCode(`${newName}#Author`);
        setListenerCode(`${newName}#Listener`);
    }

    // TODO confirm
    return (
        <Grid container component="main" className={classes.root}>
            <AppBarNavigation></AppBarNavigation>
            <CssBaseline/>
            <Grid item component={Paper}>
                <div className={classes.paper}>
                    <Avatar className={classes.avatar}>
                        <AssignmentIcon/>
                    </Avatar>
                    <Typography component="h1" variant="h5">
                        Create conference
                    </Typography>
                    <MuiPickersUtilsProvider utils={DateFnsUtils}>
                        <form className={classes.form} noValidate>
                            <TextField
                                variant="outlined"
                                margin="normal"
                                required
                                fullWidth
                                onChange={e => handleNameChange(e.target.value)}
                                id="name"
                                label="Conference name"
                                name="name"
                                autoComplete="name"
                                autoFocus
                            />
                            <TextField
                                variant="outlined"
                                margin="normal"
                                required
                                fullWidth
                                onChange={e => setFee(e.target.value)}
                                name="fee"
                                label="Conference fee"
                                type="text"
                                id="fee"
                            />
                            <KeyboardDatePicker
                                fullWidth
                                required
                                format="dd-MM-yyyy"
                                margin="normal"
                                disableToolbar
                                variant="inline"
                                value={abstractDeadline}
                                onChange={(date) => setAbstractDeadline(date)}
                                label="Abstract deadline"
                                id="abstractDeadline"
                                name="abstractDeadline"
                            />
                            <KeyboardDatePicker
                                fullWidth
                                value={paperDeadline}
                                onChange={(date) => setPaperDeadline(date)}
                                format="dd-MM-yyyy"
                                margin="normal"
                                disableToolbar
                                variant="inline"
                                label="Paper deadline"
                                id="paperDeadline"
                                name="paperDeadline"
                            />
                            <KeyboardDatePicker
                                fullWidth
                                required
                                value={startTime}
                                onChange={(date) => setStartTime(date)}
                                format="dd-MM-yyyy"
                                margin="normal"
                                disableToolbar
                                variant="inline"
                                label="Conference start date"
                                id="startTime"
                                name="startTime"
                            />
                            <KeyboardDatePicker
                                fullWidth
                                required
                                value={endTime}
                                onChange={(date) => setEndTime(date)}
                                format="dd-MM-yyyy"
                                margin="normal"
                                disableToolbar
                                variant="inline"
                                label="Conference end date"
                                id="endTime"
                                name="endTime"
                            />
                            <TextField
                                variant="outlined"
                                margin="normal"
                                required
                                fullWidth
                                name="chairCode"
                                label="Chair code"
                                type="text"
                                id="chairCode"
                                value={chairCode}
                            />
                            <TextField
                                variant="outlined"
                                margin="normal"
                                required
                                fullWidth
                                name="PCMemberCode"
                                label="PCMember code"
                                type="text"
                                id="PCMemberCode"
                                value={PCMemberCode}
                            />
                            <TextField
                                variant="outlined"
                                margin="normal"
                                required
                                fullWidth
                                name="authorCode"
                                label="Author code"
                                type="text"
                                id="authorCode"
                                value={authorCode}
                            />
                            <TextField
                                variant="outlined"
                                margin="normal"
                                required
                                fullWidth
                                name="listenerCode"
                                label="Listener code"
                                type="text"
                                id="listenerCode"
                                value={listenerCode}
                            />
                            <Button
                                type="submit"
                                fullWidth
                                variant="contained"
                                color="primary"
                                onClick={handleConfirmOpen}
                                className={classes.submit}
                            >
                                Add new conference
                            </Button>
                        </form>
                    </MuiPickersUtilsProvider>
                    <Dialog
                        open={confirming}
                        onClose={handleConfirmClose}
                        aria-labelledby="alert-dialog-title"
                        aria-describedby="alert-dialog-description"
                    >
                        <DialogTitle id="alert-dialog-title">
                            Are you sure you want to add conference?
                        </DialogTitle>
                        <DialogContent>
                            <DialogContentText id="alert-dialog-description">
                                Once you confirm this, there is no way back!
                            </DialogContentText>
                        </DialogContent>
                        <DialogActions>
                            <Button onClick={handleConfirmClose} color="primary">
                                No!
                            </Button>
                            <Button onClick={handleConfirmAgree} color="primary">
                                Yes!
                            </Button>
                        </DialogActions>
                    </Dialog>
                </div>
            </Grid>
        </Grid>
    );
}
