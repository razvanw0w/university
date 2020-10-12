import axios from 'axios';
import React, {useState} from 'react';
import Grid from '@material-ui/core/Grid';
import Typography from '@material-ui/core/Typography';
import TextField from '@material-ui/core/TextField';
import { makeStyles } from '@material-ui/core/styles';
import CssBaseline from '@material-ui/core/CssBaseline';
import AppBar from '@material-ui/core/AppBar';
import Toolbar from '@material-ui/core/Toolbar';
import Paper from '@material-ui/core/Paper';
import Button from '@material-ui/core/Button';
import Link from '@material-ui/core/Link';
import {white} from 'color-name';
import {red} from '@material-ui/core/colors';
import AppBarNavigation from './AppBarNavigation';
import FormControl from '@material-ui/core/FormControl';
import InputLabel from '@material-ui/core/InputLabel';
import Select from '@material-ui/core/Select';
import MenuItem from '@material-ui/core/MenuItem';




const useStyles = makeStyles((theme) => ({
    appBar: {
        position: 'relative',
    },
    layout: {
        width: 'auto',
        marginLeft: theme.spacing(2),
        marginRight: theme.spacing(2),
        [theme.breakpoints.up(600 + theme.spacing(2) * 2)]: {
            width: 600,
            marginLeft: 'auto',
            marginRight: 'auto',
        },
    },
    paper: {
        marginTop: theme.spacing(3),
        marginBottom: theme.spacing(3),
        padding: theme.spacing(2),
        [theme.breakpoints.up(600 + theme.spacing(3) * 2)]: {
            marginTop: theme.spacing(6),
            marginBottom: theme.spacing(6),
            padding: theme.spacing(3),
        },
    },
    stepper: {
        padding: theme.spacing(3, 0, 5),
    },
    buttons: {
        display: 'flex',
        justifyContent: 'flex-end',
    },
    button: {
        marginTop: theme.spacing(2),
        marginLeft: theme.spacing(28),
    },
    input: {
        marginTop: theme.spacing(1),
        marginLeft: theme.spacing(0)
    },
    root: {
        flexGrow: 1,
    },
    title: {
        flexGrow: 1,
    },

    a:{
        display: 'block',
        color: white,
        textAlign: 'center',
        // eslint-disable-next-line no-restricted-globals
        float: screenLeft,
        //padding: 14px 16px,
        textDecorationColor: red,
    },
    formControl: {
        minWidth: 120,
    },
}));

export default function SubmitMetaInfo() {
    const classes = useStyles();
    const [authors, setAuthors] = useState("");
    const [keywords, setKeywords] = useState("");
    const [title, setTitle] = useState("");
    const [topics, setTopics] = useState("");
    const [open, setOpen] = useState(false);
    var abstractFile;


    function handleAbstractFile(event) {
        console.log("Handling abstract file");
        event.preventDefault();
        abstractFile = event.target.files[0];
    }

    function uploadAbstract(event){
        console.log(topics);
        event.preventDefault();
        console.log("Entering upload file to server  function");
        const formData = new FormData();
        var fileInput = null;
        console.log(abstractFile);
        fileInput = abstractFile;
        let idAuthor = parseInt(window.sessionStorage.getItem("userId"));
        formData.set('file', fileInput, fileInput.name);
        formData.set('authors', authors);
        formData.set("keywords", keywords);
        formData.set("title", title);
        formData.set("authorId",idAuthor);
        formData.set("topics", topics);
        formData.set("authorId", window.sessionStorage.getItem("userId"));
        console.log(fileInput);
        console.log("Now sending file. May God bless us");
        axios.defaults.baseURL = "http://localhost:8080";

        axios({
            method: 'post',
            url: '/proposals/addabstract/',
            data: formData,
            headers: {'Content-Type': 'multipart/form-data' }
        })
            .then(function (response) {
                //handle success
                console.log(response);
                window.alert("meta-info added!");
            })
            .catch(function (response) {
                //handle error
                console.log(response);
            });
    }


    // const handleChange = (event) => {
    //     setTopics(event.target.value);
    // };

    // const handleClose = () => {
    //     setOpen(false);
    // };
    //
    // const handleOpen = () => {
    //     setOpen(true);
    // };


    return (

        <React.Fragment>
            <AppBarNavigation></AppBarNavigation>
            <br/>
            <CssBaseline />
            <main className={classes.layout}>
                <Paper className={classes.paper}>
                    <Typography component="h1" variant="h4" align="center">
                        Upload Meta-Info
                    </Typography>
                    <Grid container spacing={3}>
                        <Grid item xs={12}>
                            <TextField
                                required
                                id="title"
                                name="title"
                                label="Title"
                                fullWidth
                                autoComplete="title"
                                onChange={e => setTitle(e.target.value)}
                            />
                        </Grid>
                        <Grid item xs={12}>
                            <TextField
                                required
                                id="keywords"
                                name="keywords"
                                label="Keywords"
                                fullWidth
                                autoComplete="keywords"
                                onChange={e => setKeywords(e.target.value)}
                            />
                        </Grid>
                        <Grid item xs={12}>
                            {/*<TextField*/}
                            {/*    required*/}
                            {/*    id="topics"*/}
                            {/*    name="topics"*/}
                            {/*    label="Topics"*/}
                            {/*    fullWidth*/}
                            {/*    autoComplete="topics"*/}
                            {/*    onChange={e => setTopics(e.target.value)}*/}
                            {/*/>*/}
                        <FormControl className={classes.formControl}>
                            <InputLabel id="topicsLabel">Topics</InputLabel>
                            <Select
                                id="topics"
                                name="topics"
                                label="Topics"
                                fullWidth
                                open={open}
                                value={topics}
                                onChange={e => setTopics(e.target.value)}
                                onOpen={e => setOpen(true)}
                                onClose={e => setOpen(false)}
                            >
                                <MenuItem value="">
                                    <em>None</em>
                                </MenuItem>
                                <MenuItem value={"health"}>Health</MenuItem>
                                <MenuItem value={"social"}>Social</MenuItem>
                                <MenuItem value={"politics"}>Politics</MenuItem>
                                <MenuItem value={"entertainment"}>Entertainment</MenuItem>
                                <MenuItem value={"sports"}>Sports</MenuItem>
                                <MenuItem value={"lifestyle"}>Lifestyle</MenuItem>
                                <MenuItem value={"technology"}>Technology</MenuItem>
                            </Select>
                        </FormControl>
                        </Grid>
                        <Grid item xs={12}>
                            <TextField
                                id="listAuthors"
                                name="listAuthors"
                                label="List of authors"
                                fullWidth
                                autoComplete="listAuthors"
                                onChange={e => setAuthors(e.target.value)}
                            />
                        </Grid>
                        <Grid item xs={12}>
                            Upload abstract
                            <br/>
                            <Button fullWidth color="primary">
                                {<input className={classes.input} onChange={handleAbstractFile} type="file"/>}
                            </Button>
                        </Grid>
                    </Grid>
                    <Button
                        variant="contained"
                        color="primary"
                        onClick={uploadAbstract}
                        className={classes.button}
                    >Upload
                    </Button>
                </Paper>
            </main>
        </React.Fragment>
    );
}
