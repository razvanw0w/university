import {makeStyles} from "@material-ui/core/styles";
import CssBaseline from "@material-ui/core/CssBaseline";
import Grid from "@material-ui/core/Grid";
import Paper from "@material-ui/core/Paper";
import Box from "@material-ui/core/Box";
import Button from "@material-ui/core/Button";
import React, {useEffect, useState} from "react";
import AppBarNavigation from "./AppBarNavigation";
import axios from "axios";


const useStyles = makeStyles((theme) => ({
    root: {
        
        display: 'flex',
        flexDirection: 'row',
        justifyContent: 'center',
        backgroundSize: 'cover',
        backgroundRepeat: 'no-repeat'
    },
    paperBack: {
        height: '110%',
        width: '100%',
        position: 'relative',
        top: '5px',
        display: 'flex',
        flexDirection: 'column',
        textAlign: 'center'
    },

    openButton: {
        width: '90%',
        color: 'white',
        fontSize: '13px',
        backgroundColor: '#4287f5',
        textDecoration: 'none',
        position: 'relative',
        top: '13px',
        marginLeft:'7px'
    },

    link: {
        textDecoration: 'none'
    },

    text: {
        fontSize: '15px',
        fontFamily: 'sans-serif',
        position: 'relative',
        top: '10px',
        fontWeight: 'bold'
    },

    qualifiers: {
        display: 'flex',
        flexDirection: 'column',
        alignItems: 'center',
        position: 'relative',
        top: '20px',
    },

    strongAccept: {
        width: '80%',
        fontSize: '13px',
        color: 'black',
        backgroundColor: 'green',
        border: '1px solid black',
        margin: '3px'
    },

    accept: {
        width: '80%',
        fontSize: '13px',
        color: 'black',
        backgroundColor: 'rgb(51, 204, 51)',
        border: '1px solid black',
        margin: '3px'
    },

    weakAccept: {
        width: '80%',
        fontSize: '13px',
        color: 'black',
        backgroundColor: 'rgb(153, 255, 153)',
        border: '1px solid black',
        margin: '3px'
    },

    border: {
        width: '80%',
        fontSize: '13px',
        color: 'black',
        backgroundColor: 'rgb(204, 255, 255)',
        border: '1px solid black',
        margin: '3px'

    },

    weakReject: {
        width: '80%',
        fontSize: '13px',
        color: 'black',
        backgroundColor: 'rgb(255, 179, 179)',
        border: '1px solid black',
        margin: '3px'
    },

    reject: {
        width: '80%',
        fontSize: '13px',
        color: 'black',
        backgroundColor: 'rgb(255, 80, 80)',
        border: '1px solid black',
        margin: '3px'
    },

    strongReject: {
        width: '80%',
        fontSize: '13px',
        color: 'black',
        backgroundColor: 'rgb(255, 0, 0)',
        border: '1px solid black',
        margin: '3px'
    },

    container: {
        width: '20%',
        margin: '10px',
        listStyle: 'none'
    },

    ulcontainer: {
        display: 'flex',
        flexDirection: 'row',
        justifyContent: 'center',
        width: '100%'
    }


}));


export default function ReviewPCMember() {
    //window.sessionStorage.setItem("userId", "15");
    const [loading, setLoading] = useState(true);
    const [cards, setCards] = useState(null);

    function getAll() {
        axios.defaults.baseURL = "http://localhost:8080";
        return axios.get("/proposals/getToReview/" + parseInt(window.sessionStorage.getItem("userId")));
    }

    async function get() {
        try {
            setLoading(true);
            const value = await getAll();
            setCards(value.data);
            console.log(value);
        }
        catch (e) {
            console.log(e);
        }
        finally {
            setLoading(false);
        }
    }

    useEffect(() => {
        get();
    }, []);

    const classes = useStyles();

    function GiveGrade(id, grade) {
        axios.defaults.baseURL = "http://localhost:8080";
        axios.post('/proposals/review', null, {
            params: {
                id: id,
                reviewGrade: grade
            }
        })
            .then(response => {console.log(response); window.alert('grade given!')})
            .catch(error => console.log(error));
    }

    function getFile(id){
        axios.defaults.baseURL = "http://localhost:8080";
        return axios.get("/proposals/getPaper/"+id);
    }
    var g;

    function base64ToArrayBuffer(base64) {
        var binaryString = window.atob(base64);
        var binaryLen = binaryString.length;
        var bytes = new Uint8Array(binaryLen);
        for (var i = 0; i < binaryLen; i++) {
            var ascii = binaryString.charCodeAt(i);
            bytes[i] = ascii;
        }
        return bytes;
    }
    

    async function getPaper(id) {
        try {
            g = await getFile(id)
            console.log(g)
            var arrrayBuffer = base64ToArrayBuffer(g.data.file);
            var blob = new Blob([arrrayBuffer], {type: "application/pdf"});
            var link = window.URL.createObjectURL(blob);
            window.open(link,'', 'height=650,width=840');
            
        }
        catch (e) {
            console.log(e);
        }
        finally {
        }
    }

    function ProposalList(props) {
        const proposals = props.proposals;
        console.log(proposals);
        const items = proposals.map(proposal => <li key={proposal.id} className={classes.container}>
            <Grid item component={Paper} elevation={6} square className={classes.paperBack}>
                <Button
                    title={"Open the proposal"}
                    type="submit"
                    variant="contained"
                    className={classes.openButton}
                    onClick={() => getPaper(proposal.id)}>
                    Open Proposal
                </Button>
                <p className={classes.text}> Title: {proposal.title}</p>
                <Box className={classes.text}>
                    Select one qualifier:
                </Box>
                <div className={classes.qualifiers}>
                    <Button className={classes.strongAccept} onClick={() => GiveGrade(proposal.id, 7)}>
                        Strong accept
                    </Button>
                    <Button className={classes.accept} onClick={() => GiveGrade(proposal.id, 6)}>
                        Accept
                    </Button>
                    <Button className={classes.weakAccept} onClick={() => GiveGrade(proposal.id, 5)}>
                        Weak accept
                    </Button>
                    <Button className={classes.border} onClick={() => GiveGrade(proposal.id, 4)}>
                        Borderline Paper
                    </Button>
                    <Button className={classes.weakReject} onClick={() => GiveGrade(proposal.id, 3)}>
                        Weak Reject
                    </Button>
                    <Button className={classes.reject} onClick={() => GiveGrade(proposal.id, 2)}>
                        Reject
                    </Button>
                    <Button className={classes.strongReject} onClick={() => GiveGrade(proposal.id, 1)}>
                        Strong reject
                    </Button>
                </div>
            </Grid>
        </li>);
        return (
            <ul className={classes.ulcontainer}>{items}</ul>
        );
    }



    return loading ? <p>"Loading..."</p>: (
        <Grid container component="main" className={classes.root}>
            <AppBarNavigation></AppBarNavigation>
            <br/><br/><br/>
            <CssBaseline />
            <ProposalList proposals={cards}/>
        </Grid>
    )
}
