import React from 'react';
import AppBar from '@material-ui/core/AppBar';
import Button from '@material-ui/core/Button';
import Card from '@material-ui/core/Card';
import CardActions from '@material-ui/core/CardActions';
import CardContent from '@material-ui/core/CardContent';
import CardHeader from '@material-ui/core/CardHeader';
import CssBaseline from '@material-ui/core/CssBaseline';
import Grid from '@material-ui/core/Grid';
import StarIcon from '@material-ui/icons/StarBorder';
import Toolbar from '@material-ui/core/Toolbar';
import Typography from '@material-ui/core/Typography';
import Link from '@material-ui/core/Link';
import {makeStyles} from '@material-ui/core/styles';
import Container from '@material-ui/core/Container';
import Box from '@material-ui/core/Box';
import axios from 'axios';
import AuthorPanel from "./AuthorPanel";

function Copyright() {
    return (
        <Typography variant="body2" color="textSecondary" align="center">
            {'Copyright © '}
            <Link color="inherit" href="https://material-ui.com/">
                Your Website
            </Link>{' '}
            {new Date().getFullYear()}
            {'.'}
        </Typography>
    );
}

const useStyles = makeStyles((theme) => ({
    '@global': {
        ul: {
            margin: 0,
            padding: 0,
            listStyle: 'none',
        },
    },
    appBar: {
        borderBottom: `1px solid ${theme.palette.divider}`,
    },
    toolbar: {
        flexWrap: 'wrap',
    },
    toolbarTitle: {
        flexGrow: 1,
    },
    link: {
        margin: theme.spacing(1, 1.5),
    },
    heroContent: {
        padding: theme.spacing(8, 0, 6),
    },
    cardHeader: {
        backgroundColor:
            theme.palette.type === 'light' ? theme.palette.grey[200] : theme.palette.grey[700],
    },
    cardPricing: {
        display: 'flex',
        justifyContent: 'center',
        alignItems: 'baseline',
        marginBottom: theme.spacing(2),
    },
    footer: {
        borderTop: `1px solid ${theme.palette.divider}`,
        marginTop: theme.spacing(8),
        paddingTop: theme.spacing(3),
        paddingBottom: theme.spacing(3),
        [theme.breakpoints.up('sm')]: {
            paddingTop: theme.spacing(6),
            paddingBottom: theme.spacing(6),
        },
    },
}));

const tiers = [
    {
        title: 'Submit Meta-Info',
        price: '',
        description: ['Submit key words', 'of your application', 'right here'],
        buttonText: 'Submit',
        buttonVariant: 'outlined',
    },
    {
        title: 'Pay fee',
        subheader: '(Necessary to participate)',
        price: '',
        description: [
            'The fee MUST',
            'be payed until',
            'the given deadline'
        ],
        buttonText: 'Pay Now',
        buttonVariant: 'contained',
    },
    {
        title: 'Submit Paper',
        price: '',
        description: [
            'Here you can',
            'submit your full work',
            'text files please'
        ],
        buttonText: 'Submit',
        buttonVariant: 'outlined',
    },
];
const footers = [
    {
        title: 'Company',
        description: ['Team', 'History', 'Contact us', 'Locations'],
    },
    {
        title: 'Features',
        description: ['Cool stuff', 'Random feature', 'Team feature', 'Developer stuff', 'Another one'],
    },
    {
        title: 'Resources',
        description: ['Resource', 'Resource name', 'Another resource', 'Final resource'],
    },
    {
        title: 'Legal',
        description: ['Privacy policy', 'Terms of use'],
    },
];

export default function Pricing() {
    const classes = useStyles();

    var metaInfoFile = null;
    var paperFile = null;

    function AppBarSteering(){
        if(window.sessionStorage.getItem("userType")=="author")
        {
            return <AuthorPanel></AuthorPanel>
        }
        else
            return null;
    }

    function uploadFileToServer(event, sectionName){
        event.preventDefault();
        console.log("Entering upload file to server  function");
        const formData = new FormData();
        // var fileInput  = document.querySelector('input[type=file]').files[0];
        // console.log(fileInput);
        var fileInput = null;
        var fileCategory = null;
        if(sectionName === "Submit Meta-Info"){
            fileInput = metaInfoFile;
            fileCategory = "meta-info";
        }
        else{
            fileInput = paperFile;
            fileCategory = "paper";
        }
        let userId = window.sessionStorage.getItem("userId")
        formData.set('file', fileInput, fileInput.name);
        formData.set('userId',userId);
        formData.set('fileCategory', fileCategory)
        console.log(fileInput);
        console.log("Now sending file. May God bless us");
        axios.defaults.baseURL = "http://localhost:8080";

        axios({
            method: 'post',
            url: '/proposals/upload/',
            data: formData,
            headers: {'Content-Type': 'multipart/form-data' }
        })
            .then(function (response) {
                //handle success
                console.log(response);
            })
            .catch(function (response) {
                //handle error
                console.log(response);
            });
    }

    function handleMetaInfoFile(event) {
        console.log("Handling meta info file");
        event.preventDefault();
        metaInfoFile = event.target.files[0];
        event.target.value = null;
    }
    function handlePaperFile(event) {
        console.log("Handling paper file");
        event.preventDefault();
        paperFile = event.target.files[0];
        event.target.value = null;
    }
    return (
        <React.Fragment>
            <AppBarSteering></AppBarSteering>
            <CssBaseline />
            <AppBar position="static" color="default" elevation={0} className={classes.appBar}>
                <Toolbar className={classes.toolbar}>
                    <Typography variant="h6" color="inherit" noWrap className={classes.toolbarTitle}>
                        Company name
                    </Typography>
                    <nav>
                        <Link variant="button" color="textPrimary" href="#" className={classes.link}>
                            Features
                        </Link>
                        <Link variant="button" color="textPrimary" href="#" className={classes.link}>
                            Enterprise
                        </Link>
                        <Link variant="button" color="textPrimary" href="#" className={classes.link}>
                            Support
                        </Link>
                    </nav>
                    <Button href="#" color="primary" variant="outlined" className={classes.link}>
                        Login
                    </Button>
                </Toolbar>
            </AppBar>
            {/* Hero unit */}
            <Container maxWidth="sm" component="main" className={classes.heroContent}>
                <Typography component="h1" variant="h2" align="center" color="textPrimary" gutterBottom>
                    Author Control Panel
                </Typography>
                <Typography variant="h5" align="center" color="textSecondary" component="p">
                    Here you can control your conference participation details
                </Typography>
            </Container>
            {/* End hero unit */}
            <Container maxWidth="md" component="main">
                <Grid container spacing={5} alignItems="flex-end">
                    {tiers.map((tier) => (
                        // Enterprise card is full width at sm breakpoint
                        <Grid item key={tier.title} xs={12} sm={tier.title === 'Enterprise' ? 12 : 6} md={4}>
                            <Card>
                                <CardHeader
                                    title={tier.title}
                                    subheader={tier.subheader}
                                    titleTypographyProps={{ align: 'center' }}
                                    subheaderTypographyProps={{ align: 'center' }}
                                    action={tier.title === 'Pro' ? <StarIcon /> : null}
                                    className={classes.cardHeader}
                                />
                                <CardContent>
                                    {/*<div className={classes.cardPricing}>*/}
                                    {/*    <Typography component="h2" variant="h3" color="textPrimary">*/}
                                    {/*        ${tier.price}*/}
                                    {/*    </Typography>*/}
                                    {/*    <Typography variant="h6" color="textSecondary">*/}
                                    {/*        /mo*/}
                                    {/*    </Typography>*/}
                                    {/*</div>*/}
                                    <ul>
                                        {tier.description.map((line) => (
                                            <Typography component="li" variant="subtitle1" align="center" key={line}>
                                                {line}
                                            </Typography>
                                        ))}
                                    </ul>
                                </CardContent>
                                <CardActions>
                                    <Button fullWidth variant={tier.buttonVariant} color="primary">
                                        {tier.title === 'Submit Meta-Info' &&
                                        <input className={classes.input} onChange={handleMetaInfoFile} type="file"/>}
                                        {tier.title === 'Submit Paper' &&
                                        <input className={classes.input} onChange={handlePaperFile} type="file"/>}
                                        {tier.title === 'Pay fee' && tier.title}
                                    </Button>
                                    <br />
                                    {tier.title !== 'Pay fee' && <Button fullWidth onClick={(event) => {
                                        uploadFileToServer(event,tier.title)
                                    }} variant={tier.buttonVariant} color="primary">
                                        {tier.title}
                                    </Button>}
                                </CardActions>
                            </Card>
                        </Grid>
                    ))}
                </Grid>
            </Container>
            {/* Footer */}
            <Container maxWidth="md" component="footer" className={classes.footer}>
                <Grid container spacing={4} justify="space-evenly">
                    {footers.map((footer) => (
                        <Grid item xs={6} sm={3} key={footer.title}>
                            <Typography variant="h6" color="textPrimary" gutterBottom>
                                {footer.title}
                            </Typography>
                            <ul>
                                {footer.description.map((item) => (
                                    <li key={item}>
                                        <Link href="#" variant="subtitle1" color="textSecondary">
                                            {item}
                                        </Link>
                                    </li>
                                ))}
                            </ul>
                        </Grid>
                    ))}
                </Grid>
                <Box mt={5}>
                    <Copyright />
                </Box>
            </Container>
            {/* End footer */}
        </React.Fragment>
    );
}
