package ro.stackoverflowpioneers.ConferenceManagementSystem.Controller;

import org.junit.Before;
import org.junit.Test;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.springframework.http.MediaType;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.ResultActions;
import org.springframework.test.web.servlet.request.MockMvcRequestBuilders;
import org.springframework.test.web.servlet.setup.MockMvcBuilders;
import ro.stackoverflowpioneers.ConferenceManagementSystem.DTO.ConferenceDTO;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Domain.Conference;
import ro.stackoverflowpioneers.ConferenceManagementSystem.Repository.*;

import java.util.Arrays;
import java.util.List;

import static org.hamcrest.Matchers.hasSize;
import static org.hamcrest.Matchers.is;
import static org.mockito.Mockito.when;
import static org.mockito.MockitoAnnotations.initMocks;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.*;

//@RunWith(MockitoJUnitRunner.class)
public class ConferenceControllerTest {
    private MockMvc mockMvc;

    @InjectMocks
    private ConferenceController conferenceController;

    @Mock
    private ConferenceRepository conferenceRepository;

    @Mock
    private SteeringCommitteeMemberRepository steeringCommitteeMemberRepository;

    @Mock
    private PCMemberRepository pcMemberRepository;

    @Mock
    private ProposalRepository proposalRepository;

    @Mock
    private ConferenceSectionRepository conferenceSectionRepository;

    @Mock
    private AuthorRepository authorRepository;

    @Mock
    private RoomRepository roomRepository;

    @Mock
    private UserRepository userRepository;

    private Conference conference1;
    private Conference conference2;
    private ConferenceDTO conferenceDTO1;
    private ConferenceDTO conferenceDTO2;

    @Before
    public void setup() throws Exception {
        initMocks(this);
        this.mockMvc = MockMvcBuilders.standaloneSetup(conferenceController).build();
        initData();
    }

    @Test
    public void getAllConference() throws Exception {
        List<Conference> conferences = Arrays.asList(conference1, conference2);

        when(conferenceRepository.findAll()).thenReturn(conferences);

        ResultActions resultActions = mockMvc.perform(MockMvcRequestBuilders.get("/conferences/all"))
                .andExpect(status().isOk())
                .andExpect(content().contentType(MediaType.APPLICATION_JSON))
                .andExpect(jsonPath("$", hasSize(2)))
                .andExpect(jsonPath("$[0].id", is(1)))
                .andExpect(jsonPath("$[0].name", is("c1")))
                .andExpect(jsonPath("$[0].authorCode", is("c1#Author")))
                .andExpect(jsonPath("$[0].listenerCode", is("c1#Listener")))
                .andExpect(jsonPath("$[1].id", is(2)))
                .andExpect(jsonPath("$[1].name", is("c2")))
                .andExpect(jsonPath("$[1].authorCode", is("c2#Author")))
                .andExpect(jsonPath("$[1].listenerCode", is("c2#Listener")));
    }

    private void initData() {
        conference1 = new Conference();
        conference1.setId(1);
        conference1.setName("c1");
        conference1.setAuthorCode("c1#Author");
        conference1.setListenerCode("c1#Listener");
        conference2 = new Conference();
        conference2.setId(2);
        conference2.setName("c2");
        conference2.setAuthorCode("c2#Author");
        conference2.setListenerCode("c2#Listener");

        conferenceDTO1 = createConferenceDTO(conference1);
        conferenceDTO2 = createConferenceDTO(conference2);
    }

    private ConferenceDTO createConferenceDTO(Conference conference) {
        return new ConferenceDTO(
                conference.getId(),
                conference.getName(),
                conference.getAuthorCode(),
                conference.getListenerCode()
        );
    }
}
