import React, {useEffect, useState} from "react";

import axios from "axios"
import Box from "@material-ui/core/Box"
import {makeStyles} from "@material-ui/core/styles";
import Button from "@material-ui/core/Button";
import Grid from "@material-ui/core/Grid";
import CssBaseline from "@material-ui/core/CssBaseline";
import Paper from "@material-ui/core/Paper";
import AppBarNavigation from "./AppBarNavigation";

const useStyles = makeStyles((theme) => ({
    root: {
        height: '100vh',
        width: '100vw',
        display: 'flex',
        justifyContent: 'center',
        
        backgroundSize: 'cover',
        backgroundRepeat: 'no-repeat',
        backgroundAttachment: 'fixed',
        textAlign: 'center',
        position: 'sticky'
    },

    container: {
      width: '100%',
      height: '100%',
        display: 'flex',
        flexWrap: 'wrap',
        justifyContent: 'center',
        padding: '0',
        margin: '0'
    },

    title: {
      fontSize: '30px',
        textDecoration: 'underline'
    },

    proposal: {
        listStyle: 'none',
        width: '18%',
        height: '50%',
        margin: '10px'
    },

    paperBack: {
        margin: '0',
        width: '100%',
        height: '100%',
        backgroundColor:'#f0ecdd'
    },

    item: {
        listStyle: 'none',
        position: 'relative',
        left: '-17px'
    },

    preview: {
      position: 'relative',
        top: '20px',
        color: 'white',
        backgroundColor: '#4287f5',
        width: '70%'
    },

    buttons: {
        position: 'relative',
        top: '24px'
    },

    accept: {
        color: 'white',
        backgroundColor: '#1ee345'
    },

    refuse: {
        color: 'white',
        backgroundColor: '#e04128',
        marginTop: '10px'
    },

    aitem: {
        textDecoration: 'none'
    },

}));




export default function BiddingPCMember() {
    const [loading, setLoading] = useState(true);
    const [cards, setCards] = useState(null);

    function RefuseProposal(id) {
        console.log(id);
        console.log(window.sessionStorage.getItem("userId"));
        axios.defaults.baseURL = "http://localhost:8080";
        axios.post('/proposals/refuse', null, {
            params: {
                id: id,
                pcMemberId: parseInt(window.sessionStorage.getItem("userId"))
            }
        })
            .then(response => console.log(response))
            .catch(error => console.log(error));
    }

    function getAll() {
        axios.defaults.baseURL = "http://localhost:8080";
        return axios.get("/proposals/getall", {params: {
            conferenceId: window.sessionStorage.getItem("conferenceId")
        }});
    }

    async function get() {
        try {
            setLoading(true);
            const value = await getAll();
            setCards(value.data);
        }
        catch (e) {
            console.log(e);
        }
        finally {
            setLoading(false);
        }
    }
    
    function AuthorList(props) {
        const authors = props.authors.split(',');
        var i = 0;
        const items = authors.map((author) => {
            i += 1;
            return <li key={i} className={classes.item} title={"Author"}>{author}</li>
        });
        return (
            <ul>{items}</ul>
        );
    }

    
    function getFile(id){
        axios.defaults.baseURL = "http://localhost:8080";
        return axios.get("/proposals/getAbstract/"+id);
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
    

    async function getAbstract(id) {
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
        const items = proposals.map((proposal) => <li key={proposal.id} id={proposal.id} className={classes.proposal}>
            <Grid item component={Paper} elevation={6} square className={classes.paperBack}>
                <div className={classes.paper}>
                    <Box className={classes.title}
                         title={"Proposal Title"}>
                        {proposal.title}
                    </Box>

                    <Grid className={classes.list}>
                        <AuthorList authors={proposal.authors}/>
                    </Grid>
                    <Button type="submit"
                            variant="contained"
                            className={classes.preview}
                            title={"Preview"}
                            onClick={() => getAbstract(proposal.id)}>
                        Preview abstract
                    </Button>
                   
                    <div className={classes.buttons}>
                        <Button type="submit"
                                variant="contained"
                                className={classes.accept}
                                title={"Accept to review"}
                                onClick={e=>window.alert("you accepted this paper!")}>
                            Accept
                        </Button>
                        <br></br>
                        <Button type="submit"
                                variant="contained"
                                className={classes.refuse}
                                title={"Refuse the proposal"}
                                id={proposal.id}
                                onClick={() => RefuseProposal(proposal.id)}
                                >
                            Refuse
                        </Button>
                    </div>

                </div>
            </Grid>
        </li>);
        return (
            <ul className={classes.container}>{items}</ul>
        );
    }

    useEffect(() => {
        get();
    }, []);

    const classes = useStyles();
    return loading ? <p>"Loading..."</p>: (
            <Grid container component="main" className={classes.root}>
                <AppBarNavigation></AppBarNavigation>
                <br/><br/><br/>
                <CssBaseline />

                <ProposalList proposals={cards}/>
            </Grid>
        );

}
