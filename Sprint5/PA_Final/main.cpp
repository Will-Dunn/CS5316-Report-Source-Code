#include <iostream>
#include <../../lib/OleanderStemmingLibrary-master/include/olestem/stemming/english_stem.h>
#include <string>
#include <../../lib/dirent.h>
#include <sstream>
#include <vector>
//Elliot Boesch
#include <../../lib/rapidjson-master/include/rapidjson/document.h>
#include <../../lib/rapidjson-master/include/rapidjson/writer.h>
#include <../../lib/rapidjson-master/include/rapidjson/istreamwrapper.h>
#include <../../lib/rapidjson-master/include/rapidjson/ostreamwrapper.h>
#include <../../lib/rapidjson-master/include/rapidjson/stringbuffer.h>
#include "term.h"
#include "stemmer.h"
#include "avltree.h"
#include "documentparser.h"
#include "index.h"
#include "type2.h"
#include "hashtable.h"

#include "query.h"
#include "ui.h"
#include <iostream>
#include <bitset>
#include <fstream>
#include <chrono>

using namespace std::chrono;
using namespace rapidjson;
using namespace std;
static bool m1 = false;

void createDataSet(int fileSetSize, string datafile, string directory, string sentenceList) {
   // string words[5] = {"Stroke", "Grin", "Building", "Thinkable", "rabbits"};
    string words[200] = {"Stroke", "Smell", "Building", "Thinkable", "Skillful", "Available", "Name", "Wail", "Pigs",
                         "Bikes", "Seashore", "Soggy", "Caring", "Repeat", "Phone", "Suck", "Grin", "arrive", "pan",
                         "wakeful", "third", "prick", "possess", "thank", "rabbits", "fresh", "spectacular", "business",
                         "birds", "type", "waves", "sophisticated", "cooing", "cloudy", "vast", "gleaming", "worry",
                         "nauseating", "grade", "ring", "wax", "juicy", "repair", "pedal", "lacking", "alive",
                         "knowledge", "weight", "liquid", "chubby", "fax", "rely", "screeching", "present", "crooked",
                         "silly", "oranges", "need", "confess", "selfish", "deceive", "mine", "suggest", "army",
                         "school", "nutty", "open", "flag", "pies", "garrulous", "whimsical", "improve", "upset",
                         "threatening", "hellish", "abaft", "connection", "crowd", "unable", "turkey", "delightful",
                         "argue", "recess", "bow", "physical", "obeisant", "ghost", "amount", "skip", "bubble",
                         "halting", "receive", "flower", "price", "push", "telephone", "green", "obscene", "slip",
                         "ray", "beds", "observation", "trees", "fumbling", "irate", "lucky", "violent", "challenge",
                         "overflow", "cold", "craven", "badge", "pinch", "uncle", "meddle", "detail", "dirt", "fine",
                         "beg", "attack", "blush", "vigorous", "giraffe", "part", "lethal", "compare", "join",
                         "damaged", "sin", "crazy", "furniture", "carriage", "cross", "allow", "color", "mysterious",
                         "eatable", "battle", "naughty", "radiate", "subsequent", "theory", "permissible", "honorable",
                         "like", "chilly", "rightful", "dog", "dinosaurs", "blood", "rustic", "possible", "escape",
                         "zip", "last", "long-term", "chew", "protest", "flavor", "invention", "hands", "juvenile",
                         "functional", "crack", "scale", "abhorrent", "bare", "breathe", "undress", "unbiased",
                         "snakes", "knowledgeable", "acoustics", "thoughtful", "phobic", "tap", "circle", "guarded",
                         "continue", "womanly", "wasteful", "sincere", "direful", "dramatic", "wanting", "ablaze",
                         "near", "pail", "flat", "can", "squash", "bored", "stew", "mist", "attach", "foamy", "tangy",
                         "window", "taste", "coast"};
    //int totals[5]={0,0,0,0,0};
    int totals[200] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0};
    ofstream os;
    ofstream os1;
    ofstream os2;
    os.open(datafile.c_str(), ofstream::out | std::ofstream::trunc);
    os2.open(sentenceList.c_str(), ofstream::out | std::ofstream::trunc);
    for (int i = 0; i < 200; i++) {
        os << words[i] << ",";
    }
    os << "\n";
    for (int j = 0; j < fileSetSize; j++) {
        string fname = directory + "/" + to_string(j) + ".json";
        os1.open(fname.c_str(), ofstream::out | ofstream::trunc);

        int counts[200] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        //int counts[5]={0,0,0,0,0};
        os1 << "{\n"
               "  \"resource_uri\": \"https://www.courtlistener.com/api/rest/v3/opinions/" << to_string(j + 1)
            << "/\",\n"
               "  \"id\":" << to_string(j + 1) << ",\n"
                                                  "  \"absolute_url\": \"/opinion/" << to_string(j + 1)
            << "/southern-pacific-co-v-haglund/\",\n"
               "  \"cluster\": \"https://www.courtlistener.com/api/rest/v3/clusters/" << to_string(j + 1) << "/\",\n"
                                                                                                             "  \"author\": \"https://www.courtlistener.com/api/rest/v3/people/2839/\",\n"
                                                                                                             "  \"joined_by\": [],\n"
                                                                                                             "  \"author_str\": \"\",\n"
                                                                                                             "  \"per_curiam\": false,\n"
                                                                                                             "  \"date_created\": \"2010-04-28T16:48:45Z\",\n"
                                                                                                             "  \"date_modified\": \"2017-03-24T04:10:15.071063Z\",\n"
                                                                                                             "  \"type\": \"010combined\",\n"
                                                                                                             "  \"sha1\": \"3642e46ed88ae434cfd453f8534bcf6db7e969c8\",\n"
                                                                                                             "  \"page_count\": null,\n"
                                                                                                             "  \"download_url\": null,\n"
                                                                                                             "  \"local_path\": null,\n"
                                                                                                             "  \"plain_text\": \"\",\n"
                                                                                                             "  \"html\": \"<p class=\\\"case_cite\\\">277 U.S. 304</p>\\n    <p class=\\\"case_cite\\\">48 S.Ct. 510</p>\\n    <p class=\\\"case_cite\\\">72 L.Ed. 892</p>\\n    <p class=\\\"parties\\\">SOUTHERN PAC. CO.<br>v.<br>HAGLUND et al.  SAME  v.  MOORE SHIPBUILDING CO. et al.</p>\\n    <p class=\\\"docket\\\">Nos. 472, 473.</p>\\n    <p class=\\\"date\\\">Submitted April 13, 1928.</p>\\n    <p class=\\\"date\\\">Decided May 21, 1928.</p>\\n    <div class=\\\"prelims\\\">\\n      <p class=\\\"indent\\\">Mr. William Denman, of San Francisco, Cal., for petitioner.</p>\\n      <p class=\\\"indent\\\">[Argument of Counsel from pages 305-306 intentionally omitted]</p>\\n      <p class=\\\"indent\\\">Messrs. Ira S. Lillick and J. F. Sullivan, both of San Francisco, Cal., for respondents.</p>\\n      <p class=\\\"indent\\\">Mr. Justice SANFORD delivered the opinion of the Court.</p>\\n    </div>\\n    <div class=\\\"num\\\" id=\\\"p1\\\">\\n      <span class=\\\"num\\\">1</span>\\n      <p class=\\\"indent\\\">These two suits in admiralty, which were brought in the federal court for northern California, arose out of a collision between the ferryboat Thoroughfare and the steamship Enterprise in charge of the tug Relief, in the channel of San Antonio Creek, known as the Oakland Estuary, which resulted in damages to the Thoroughfare and the Enterprise, and the killing of Ernest Haglund, a workman on the Enterprise. In No. 472 the administratrix of Haglund's estate libelled the Southern Pacific Company, the owner of the Thoroughfare, and the Rolph Navigation &amp; Coal Company, the owner of the Relief, for the damages arising from his death. In No. 473 the Moore Shipbuilding Company libelled the Thoroughfare for the damages to the Enterprise; and the Southern Pacific Company, as claimant of the Thoroughfare, brought in as third party respondents the Enterprise, the Relief and the Rolph Navigation &amp; Coal Company, to answer for the damages to the Thoroughfare.<a class=\\\"footnote\\\" href=\\\"#fn1\\\" id=\\\"fn1_ref\\\">1</a></p>\\n    </div>\\n    <div class=\\\"num\\\" id=\\\"p2\\\">\\n      <span class=\\\"num\\\">2</span>\\n      <p class=\\\"indent\\\">The suits were tried on the same evidence as to the responsibility for the collision, and were consolidated for hearing in the Circuit Court of Appeals. The District Court found that the collision was caused solely by the negligence of the Thoroughfare, without fault on the part of the Relief or the Enterprise, and entered decrees against the Southern Pacific Company for the damages to the Enterprise and the death of Haglund. These decrees were affirmed by the Circuit Court of Appeals. 19 F.(2d) 878.</p>\\n    </div>\\n    <div class=\\\"num\\\" id=\\\"p3\\\">\\n      <span class=\\\"num\\\">3</span>\\n      <p class=\\\"indent\\\">The channel of the Estuary, the great artery of commerce between San Francisco and Oakland, is 500 feet wide. The collision occurred about noon, on a clear day. The Enterprise, a steam freighter 320 feet long, which was undergoing repairs at the yard of the Moore Shipbuilding Company on the north bank of the Estuary, was let down stern foremost on a marine railway into the waters of the Estuary, and lay at right angles across the channel. She was without power, had no lookout, and had been placed by the Shipbuilding Company in charge of the Relief to be berthed at a nearby wharf on the Company's plant.<a class=\\\"footnote\\\" href=\\\"#fn2\\\" id=\\\"fn2_ref\\\">2</a> The Thoroughfare, a steam ferryboat, was then approaching at her full speed of 13 miles an hour on an easterly course through the Estuary. When about 2,900 feet away she sounded a single blast of her whistle. This was not answered by the Relief, which was then engaged in stopping the sternway of the Enterprise towards the south side of the channel. When the Thououghfare had approached within about 1,000 feet of the Enterprise, the Relief had arrested the movement of the Enterprise and was holding her dead in the water, with her stern about 100 feet from the south edge of the channel, leaving an ample opening for the passage of the Thoroughfare. At this distance the Thoroughfare again sounded a single blast of her whistle, indicating an intention to direct her course to starboard and pass in the rear of the Enterprise. This was accepted by the Relief by a like single blast. At this time the master of the Relief was aware of the presence at a considerable distance on the other side of the Enterprise of the tug Union<a class=\\\"footnote\\\" href=\\\"#fn3\\\" id=\\\"fn3_ref\\\">3</a> which, with a tow, was approaching on a westerly course near the south edge of the channel. The master of the Thoroughfare, whose view was then intercepted by the Enterprise, was not aware of the presence of the Union. After the Relief gave her answering signal the Thoroughfare continued to advance at full speed, for about 1,000 feet, heading for the 100 foot opening between the stern of the Enterprise and the edge of the channel, and not knowing what vessels might be encountered on the other side. Meanwhile the Enterprise remained at rest without any change in position. Just as the Thoroughfare was about to pass she saw the Union approaching on the other side and blew two whistles to indicate her intention of passing on the starboard side of the Union after she got clear of the Enterprise. This was accepted by two blasts from the Union. But before clearing the Enterprise the Thoroughfare suddenly changed her course to port, and struck the Enterprise. There was no occasion for this change to port. The Thoroughfare was not then in peril; the Union was about 900 feet away and had already slowed down; and the Thoroughfare would have had ample time and space after clearing the Enterprise in which to go to port and pass on the starboard side of the Union in accordance with the previous exchange of signals. And the Thoroughfare could herself have stopped within 300 feet.</p>\\n    </div>\\n    <div class=\\\"num\\\" id=\\\"p4\\\">\\n      <span class=\\\"num\\\">4</span>\\n      <p class=\\\"indent\\\">We agree with the view of both the lower courts that the collision was caused solely by the negligence of the Thoroughfare, which not only approached the passageway in the rear of the Enterprise at full speed, without knowing whether she would encounter any vessel on the other side, but needlessly commenced the execution of the passing movement with the Union before she had cleared the Enterprise; and that there was no contributing fault on the part of the Relief or the Enterprise.</p>\\n    </div>\\n    <div class=\\\"num\\\" id=\\\"p5\\\">\\n      <span class=\\\"num\\\">5</span>\\n      <p class=\\\"indent\\\">The Relief was not at fault in accepting the passing signal of the Thoroughfare. This was merely an assent to the proposed passage in the rear of the Enterprise, expressing an understanding of what the Thoroughfare proposed to do and an agreement not to endanger or thwart it by permitting an interfering change in the position of the Enterprise. See Atlas Transp. Co. v. Lee Line Steamers (C. C. A.) 235 F. 492, 495. And the Relief, being in a position to fully carry out its agreement, was under no obligation to decline the passing signal because of the approach of the Union on the other side and to sound instead a warning signal. There was nothing in the situation to indicate that the approach of the Union would prevent the Thoroughfare from passing safely, if, as the Relief had the right to assume, it were navigated with due care. See Atlas Transp. Co. v. Lee Line Steamers (C. C. A.) 238 F. 349, on petition for rehearing. The doctrine of The F. W. Wheeler (C. C. A.) 78 F. 824, that a moving tug is in fault in accepting, without warning, a passing signal when she knows that the passage is obstructed by her grounded tow whose movement she cannot control, has no application here.</p>\\n    </div>\\n    <div class=\\\"num\\\" id=\\\"p6\\\">\\n      <span class=\\\"num\\\">6</span>\\n      <p class=\\\"indent\\\">Nor was the Enterprise at fault in not having a lookout. The rule stated in The Ariadne, 13 Wall. 475, 478, 20 L. Ed. 542, as to the responsibility of a moving vessel for the failure of her lookout to discover an approaching vessel in time to avoid a collision, does not apply to a vessel in the position of the Enterprise, which was at rest, without power; and the absence of a lookout upon her did not in any manner contribute to the collision.</p>\\n    </div>\\n    <div class=\\\"num\\\" id=\\\"p7\\\">\\n      <span class=\\\"num\\\">7</span>\\n      <p class=\\\"indent\\\">Decrees affirmed.</p>\\n    </div>\\n    <div class=\\\"footnotes\\\">\\n      <div class=\\\"footnote\\\" id=\\\"fn1\\\">\\n        <a class=\\\"footnote\\\" href=\\\"#fn1_ref\\\">1</a>\\n        <p> Another tug, the Hercules, belonging to the Rolph Navigation &amp; Coal Company, which was also impleaded, is not here involved.</p>\\n      </div>\\n      <div class=\\\"footnote\\\" id=\\\"fn2\\\">\\n        <a class=\\\"footnote\\\" href=\\\"#fn2_ref\\\">2</a>\\n        <p> The Relief was assisted by the tug Hercules referred to in note 1, supra.</p>\\n      </div>\\n      <div class=\\\"footnote\\\" id=\\\"fn3\\\">\\n        <a class=\\\"footnote\\\" href=\\\"#fn3_ref\\\">3</a>\\n        <p> The Union is not brought into these suits.</p>\\n      </div>\\n    </div>\\n    \",\n"
                                                                                                             "  \"html_lawbox\": \"<div>\\n<center><b>277 U.S. 304 (1928)</b></center>\\n<center><h1>SOUTHERN PACIFIC COMPANY<br>\\nv.<br>\\nHAGLUND, ADMINISTRATRIX, ET AL.<br>\\nSAME<br>\\nv.<br>\\nMOORE SHIPBUILDING COMPANY ET AL.</h1></center>\\n<center>Nos. 472, 473.</center>\\n<center><p><b>Supreme Court of United States.</b></p></center>\\n<center>Submitted April 13, 1928.</center>\\n<center>Decided May 21, 1928.</center>\\nCERTIORARI TO THE CIRCUIT COURT OF APPEALS FOR THE NINTH CIRCUIT.\\n<p><span class=\\\"star-pagination\\\">*305</span> <i>Mr. Wm. Denman</i> submitted for petitioner.</p>\\n<p><span class=\\\"star-pagination\\\">*307</span> <i>Mr. Ira S. Lillick,</i> with whom <i>Mr. Hunt C. Hill was</i> on the briefs, submitted for the respondents, Moore Shipbuilding Company and Hildur Haglund, Administratrix.</p>\\n<p><i>Mr. J.F. Sullivan,</i> with whom <i>Messrs. Edward I. Barry</i> and <i>Theodore J. Roche</i> were on the brief, submitted for the respondent, Rolph Navigation &amp; Coal Company.</p>\\n<p><span class=\\\"star-pagination\\\">*306</span> MR. JUSTICE SANFORD delivered tile opinion of the Court.</p>\\n<p>These two suits in admiralty, which were brought in the federal court for northern California, arose out of a collision between the ferryboat <i>Thoroughfare</i> and the steamship <i>Enterprise</i> in charge of the tug <i>Relief,</i> in the channel of San Antonio Creek, known as the Oakland Estuary, which resulted in damages to the <i>Thoroughfare</i> and the <i>Enterprise,</i> and the killing of Ernest Haglund, a workman on the <i>Enterprise.</i> In No. 472 the administratrix of Haglund's estate libelled the Southern Pacific Co., the owner of the <i>Thoroughfare,</i> and the Rolph Navigation &amp; Coal Co., the owner of the <i>Relief,</i> for the damages arising from his death. In No. 473 the Moore Shipbuilding Co. libelled the <i>Thoroughfare</i> for the damages to the <i>Enterprise;</i> and the Southern Pacific Co., as claimant of the <i>Thoroughfare,</i> brought in as third party respondents the <i>Enterprise,</i> the <i>Relief</i> and the Rolph Navigation &amp; Coal Co., to answer for the damages to the <i>Thoroughfare.</i><sup>[1]</sup></p>\\n<p>The suits were tried on the same evidence as to the responsibility for the collision, and were consolidated for hearing in the Circuit Court of Appeals. The District Court found that the collision was caused solely by the negligence of the <i>Thoroughfare,</i> without fault on the part of the <i>Relief</i> or the <i>Enterprise,</i> and entered decrees against <span class=\\\"star-pagination\\\">*308</span> the Southern Pacific Co. for the damages to the <i>Enterprise</i> and the death of Haglund. These decrees were affirmed by the Circuit Court of Appeals. 19 F. (2d) 878.</p>\\n<p>The channel of the Estuary, the great artery of commerce between San Francisco and Oakland, is 500 feet wide. The collision occurred about noon, on a clear day. The <i>Enterprise,</i> a steam freighter 320 feet long, which was undergoing repairs at the yard of the Moore Shipbuilding Co. on the north bank of the Estuary, was let down stern foremost on a marine railway into the waters of the Estuary, and lay at right angles across the channel. She was without power, had no lookout, and had been placed by the Shipbuilding Company in charge of the <i>Relief</i> to be berthed at a nearby wharf on the Company's plant.<sup>[2]</sup> The <i>Thoroughfare,</i> a steam ferryboat, was then approaching at her full speed of 13 miles an hour on an easterly course through the Estuary. When about 2,900 feet away she sounded a single blast of her whistle. This was not answered by the <i>Relief,</i> which was then engaged in stopping the sternway of the <i>Enterprise</i> towards the south side of the channel. When the <i>Thoroughfare</i> had approached within about 1,000 feet of the <i>Enterprise,</i> the <i>Relief</i> had arrested the movement of the <i>Enterprise</i> and was holding her dead in the water, with her stern about 100 feet from the south edge of the channel, leaving an ample opening for the passage of the <i>Thoroughfare.</i> At this distance the <i>Thoroughfare</i> again sounded a single blast of her whistle, indicating an intention to direct her course to starboard and pass in the rear of the <i>Enterprise.</i> This was accepted by the <i>Relief</i> by a like single blast. At this time the master of the <i>Relief</i> was aware of the presence at a considerable distance on the other side of <span class=\\\"star-pagination\\\">*309</span> the <i>Enterprise</i> of the tug <i>Union</i><sup>[3]</sup> which, with a tow, was approaching on a westerly course near the south edge of the channel. The master of the <i>Thoroughfare,</i> whose view was then intercepted by the <i>Enterprise,</i> was not aware of the presence of the <i>Union.</i> After the <i>Relief</i> gave her answering signal the <i>Thoroughfare</i> continued to advance at full speed, for about 1,000 feet, heading for the 100 foot opening between the stern of the <i>Enterprise</i> and the edge of the channel, and not knowing what vessels might be encountered on the other side. Meanwhile the <i>Enterprise</i> remained at rest without any change in position. Just as the <i>Thoroughfare</i> was about to pass, she saw the <i>Union</i> approaching on the other side and blew two whistles to indicate her intention of passing on the starboard side of the <i>Union</i> after she got clear of the <i>Enterprise.</i> This was accepted by two blasts from the <i>Union.</i> But before clearing the <i>Enterprise</i> the <i>Thoroughfare</i> suddenly changed her course to port, and struck the <i>Enterprise.</i> There was no occasion for this change to port. The <i>Thoroughfare</i> was not then in peril; the <i>Union</i> was about 900 feet away and had already slowed down; and the <i>Thoroughfare</i> would have had ample time and space after clearing the <i>Enterprise</i> in which to go to port and pass on the starboard side of the <i>Union</i> in accordance with the previous exchange of signals. And the <i>Thoroughfare</i> could herself have stopped within 300 feet.</p>\\n<p>We agree with the view of both the lower courts that the collision was caused solely by the negligence of the <i>Thoroughfare,</i> which not only approached the passageway in the rear of the <i>Enterprise</i> at full speed, without knowing whether she would encounter any vessel on the other side, but needlessly commenced the execution of the passing movement with the <i>Union</i> before she had cleared the <span class=\\\"star-pagination\\\">*310</span> <i>Enterprise;</i> and that there was no contributing fault on the part of the <i>Relief</i> or the <i>Enterprise.</i></p>\\n<p>The <i>Relief</i> was not at fault in accepting the passing signal of the <i>Thoroughfare.</i> This was merely an assent to the proposed passage in the rear of the <i>Enterprise,</i> expressing an understanding of what the <i>Thoroughfare</i> proposed to do and an agreement not to endanger or thwart it by permitting an interfering change in the position of the <i>Enterprise.</i> See <i>Atlas Transp. Co.</i> v. <i>Lee Line Steamers</i> (C.C.A.), 235 Fed. 492, 495. And the <i>Relief,</i> being in a position to fully carry out its agreement, was under no obligation to decline the passing signal because of the approach of the <i>Union</i> on the other side and to sound instead a warning signal. There was nothing in the situation to indicate that the approach of the <i>Union</i> would prevent the <i>Thoroughfare</i> from passing safely, if, as the <i>Relief</i> had the right to assume, it were navigated with due care. See <i>Atlas Transp. Co.</i> v. <i>Lee Line Steamers</i> (C.C.A.), 238 Fed. 349, on petition for rehearing. The doctrine of <i>The F.W. Wheeler</i> (C.C.A.), 78 Fed. 824, that a moving tug is in fault in accepting, without warning, a passing signal when she knows that the passage is obstructed by her grounded tow whose movement she cannot control, has no application here.</p>\\n<p>Nor was the <i>Enterprise</i> at fault in not having a lookout. The rule stated in <i>The Ariadne,</i> 13 Wall. 475, 478, as to the responsibility of a moving vessel for the failure of her lookout to discover an approaching vessel in time to avoid a collision, does not apply to a vessel in the position of the <i>Enterprise,</i> which was at rest, without power; and the absence of a lookout upon her did not in any manner contribute to the collision.</p>\\n<p><i>Decrees affirmed.</i></p>\\n<h2>NOTES</h2>\\n<p>[1]  Another tug, the <i>Hercules,</i> belonging to the Rolph Navigation &amp; Coal Co., which was also impleaded, is not here involved.</p>\\n<p>[2]  The <i>Relief</i> was assisted by the tug <i>Hercules</i> referred to in note 1, supra,</p>\\n<p>[3]  The <i>Union</i> is not brought into these suits.</p>\\n\\n</div>\",\n"
                                                                                                             "  \"html_columbia\": null,\n"
                                                                                                             "  \"html_with_citations\": \"<p>";
        string sent = "";
        for (int i = 0; i < 700; i++) {
            int w = rand() % 200;
            if (i < 699) {
                os1 << words[w] << " ";
                sent += (words[w] + " ");
            } else {
                os1 << words[w];
                sent += (words[w]);
            }
            counts[w]++;
            //totals[w]++;
        }
        os2 << sent << endl;
        os1 << "</p>\",\n"
               "  \"extracted_by_ocr\": false,\n"
               "  \"opinions_cited\": [\n"
               "    \"https://www.courtlistener.com/api/rest/v3/opinions/88485/\",\n"
               "    \"https://www.courtlistener.com/api/rest/v3/opinions/1502028/\"\n"
               "  ]\n"
               "}";
        os1.close();
        for (int i = 0; i < 199; i++) {
            os << counts[i] << ",";
            totals[i] += counts[i];
        }
        os << counts[199] << "\n";
        totals[199] += counts[199];

    }
    for (int i = 0; i < 199; i++) {
        os << totals[i] << ",";
    }
    os << totals[199];
    os.close();
    os2.close();
    cout << "done" << endl;
}

int main(int argc, char *argv[]) {
    type2 a;
    //createDataSet(50,"Small_Test_Set_Data.csv","small-test-set","small-sentences.txt");
     UI userInterface;


    return 0;
}
